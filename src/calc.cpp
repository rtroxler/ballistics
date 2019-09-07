#include <iostream>
#include <map>
#include "calc.h"
#include "conversions.h"
#include "range_data.h"

using namespace std;

double apply_drag(int drag_function, double ballistic_coefficient, double velocity)
{
	double A=-1;
	double M=-1;
	// Assuming G7 for now, since that's all I will use
	// Build a better way to do this for all other drag functions
	if (velocity > 4200 ) { A = 1.29081656775919e-09; M = 3.24121295355962; }
	else if (velocity > 3000 ) { A = 0.0171422231434847  ; M = 1.27907168025204; }
	else if (velocity > 1470 ) { A = 2.33355948302505e-03; M = 1.52693913274526; }
	else if (velocity > 1260 ) { A = 7.97592111627665e-04; M = 1.67688974440324; }
	else if (velocity > 1110 ) { A = 5.71086414289273e-12; M = 4.3212826264889 ; }
	else if (velocity >  960 ) { A = 3.02865108244904e-17; M = 5.99074203776707; }
	else if (velocity >  670 ) { A = 7.52285155782535e-06; M = 2.1738019851075 ; }
	else if (velocity >  540 ) { A = 1.31766281225189e-05; M = 2.08774690257991; }
	else if (velocity >    0 ) { A = 1.34504843776525e-05; M = 2.08702306738884; }

	if (A!=-1 && M!=-1 && velocity >0 && velocity <10000){
		double val = A * pow(velocity, M) / ballistic_coefficient;
		return val;
	}
	else return -1;
}

/*  Arguments:
		DragFunction:  The drag function to use (G1, G2, G3, G5, G6, G7, G8)
		DragCoefficient:  The coefficient of drag for the projectile, for the supplied drag function.
		Vi:  The initial velocity of the projectile, in feet/s
		SightHeight:  The height of the sighting system above the bore centerline, in inches.
					  Most scopes fall in the 1.6 to 2.0 inch range.
		ZeroRange:  The range in yards, at which you wish the projectile to intersect yIntercept.
		yIntercept:  The height, in inches, you wish for the projectile to be when it crosses ZeroRange yards.
					This is usually 0 for a target zero, but could be any number.  For example if you wish
					to sight your rifle in 1.5" high at 100 yds, then you would set yIntercept to 1.5, and ZeroRange to 100

	Return Value:
		Returns the angle of the bore relative to the sighting system, in degrees.
*/
double calculate_zero_angle(
		int drag_function,
		double ballistic_coefficient,
		double initial_velocity,
		double sight_height,
		double zero_range,
		double y_intercept)
{
	// Integration values
	double t = 0;

	double dt = 1 / initial_velocity;
	double y = -sight_height / 12;
	double x = 0;
	double angular_delta; // The change in bore angle used to iterate over to approximate the correct zero angle

	// State variables for each loop
	double v=0, vx=0, vy=0; // velocity
	double vx1=0, vy1=0; // Last frame's velocity, used for computing average velocity
	double dv=0, dvx=0, dvy=0; // change in acceleration
	double Gx=0, Gy=0; // Gravitational acceleration

	double angle = 0; // Angle of the bore return value

	int quit = 0; // Break when quit == 1 // TODO: refactor

	// Start with a very large angular change
	angular_delta = degree_to_radian(14);

	// TODO refactor
	/// The general idea here is to start with 0 degrees elevation, and increase the elevation by 14 degrees until we are above the
	//correct elevation. Then reduce the angular change by half, and begin reducing the angle. Once we are again below the correct angle,
	//reduce the angular change by half again, and go back up. This allows for a fast successive approximation of the correct elevation,
	//usually in under 20 iterations.
	for (angle = 0; quit == 0; angle += angular_delta)
	{
		vy = initial_velocity * sin(angle);
		vx = initial_velocity * cos(angle);

		Gx=GRAVITY*sin(angle);
		Gy=GRAVITY*cos(angle);


		for (t = 0, x = 0, y = -sight_height / 12; x <= zero_range*3; t += dt)
		{
			vx1 = vx;
			vy1 = vy;
			v = pow((pow(vx,2) + pow(vy,2)), 0.5);
			dt = 1 / v;

			dv = apply_drag(drag_function, ballistic_coefficient, v);
			dvy = -dv*vy/v*dt;
			dvx = -dv*vx/v*dt;

			vx += dvx;
			vy += dvy;
			vy += dt*Gy;
			vx += dt*Gx;

			x = x+dt * (vx+vx1) / 2;
			y = y+dt * (vy+vy1) / 2;

			// Break early to save CPU time if we won't find a solution.
			if (vy<0 && y < y_intercept) {
				break;
			}
			if (vy>3*vx) {
				break;
			}
		}

		if ((y > y_intercept && angular_delta > 0) || (y < y_intercept && angular_delta < 0))
		{
			angular_delta = -angular_delta / 2;
		}

		if (fabs(angular_delta) < moa_to_radian(0.01)) quit = 1; // If our accuracy is sufficient, stop approximating
		if (angle > degree_to_radian(45)) quit = 1; // If we exceed 45 degree launch angle, then the projectile will just never get there, so stop trying
	}
	return radian_to_degree(angle);
}

double calculate_headwind(double wind_velocity, double wind_angle)
{
	double wind_angle_radians = degree_to_radian(wind_angle);
	return cos(wind_angle_radians) * wind_velocity;
}

double calculate_crosswind(double wind_velocity, double wind_angle)
{
	double wind_angle_radians = degree_to_radian(wind_angle);
	return sin(wind_angle_radians) * wind_velocity;
}

double calculate_windage(double wind_velocity, double velocity, double x, double t)
{
	double vx = wind_velocity * 17.60; // Inches per second
	return (vx * (t - x / velocity));
}

int compute_range_table(
		int drag_function,
		double ballistic_coefficient,
		double velocity,
		double sight_height,
		double shooting_angle,
		double zero_angle,
		double wind_velocity,
		double wind_angle,
		std::map<int, RangeData> &range_table) // TODO: Refactor into an array of some hash of { yardage => data } or something
{
	double t = 0;
	double dt = 0.5 / velocity;
	double v = 0;
	double vx = 0, vx1 = 0, vy = 0, vy1 = 0;
	double dv = 0, dvx = 0, dvy = 0;
	double x = 0, y = 0;

	double headwind = calculate_headwind(wind_velocity, wind_angle);
	double crosswind = calculate_crosswind(wind_velocity, wind_angle);

	double Gy = GRAVITY * cos(degree_to_radian((shooting_angle + zero_angle)));
	double Gx = GRAVITY * sin(degree_to_radian((shooting_angle + zero_angle)));

	vx = velocity * cos(degree_to_radian(zero_angle));
	vy = velocity * sin(degree_to_radian(zero_angle));

	y = -sight_height / 12;
	int n = 0;
	for ( t = 0 ;; t += dt ) // time in seconds + delta each loop
	{
		vx1 = vx, vy1 = vy;
		v = pow(pow(vx, 2) + pow(vy, 2), 0.5);
		dt = 0.5 / v;

		dv = apply_drag(drag_function, ballistic_coefficient, v + headwind);
		dvx = -(vx / velocity) * dv;
		dvy = -(vy / velocity) * dv;

		vx = vx + dt*dvx + dt * Gx;
		vy = vy + dt*dvy + dt * Gy;

		double yardage = x / 3;

		if (yardage >= n)
		{
			double windage = calculate_windage(crosswind, velocity, x, t+dt);

			RangeData data (
					yardage,
				  	y * 12,
				  	-radian_to_moa(atan(y / x)),
				  	t * dt,
				  	windage,
					radian_to_moa(atan((windage / 12) / (yardage * 3))),
					velocity,
					vx,
					vy
 					);
 			range_table.insert(make_pair(yardage, data));
			n++;
		}

		x = x + dt * (vx + vx1) / 2;
		y = y + dt * (vy + vy1) / 2;

		if (fabs(vy) > fabs(3*vx)) break;
		if (n >= __BCOMP_MAXRANGE__+1) break;
	}

	return n;
}


