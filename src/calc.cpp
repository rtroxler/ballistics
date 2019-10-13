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

	switch(drag_function) {
		case 1:
			if (velocity > 4230)            { A = 1.477404177730177e-04; M = 1.9565; }
			else if (velocity > 3680) { A = 1.920339268755614e-04; M = 1.925 ; }
			else if (velocity > 3450) { A = 2.894751026819746e-04; M = 1.875 ; }
			else if (velocity > 3295) { A = 4.349905111115636e-04; M = 1.825 ; }
			else if (velocity > 3130) { A = 6.520421871892662e-04; M = 1.775 ; }
			else if (velocity > 2960) { A = 9.748073694078696e-04; M = 1.725 ; }
			else if (velocity > 2830) { A = 1.453721560187286e-03; M = 1.675 ; }
			else if (velocity > 2680) { A = 2.162887202930376e-03; M = 1.625 ; }
			else if (velocity > 2460) { A = 3.209559783129881e-03; M = 1.575 ; }
			else if (velocity > 2225) { A = 3.904368218691249e-03; M = 1.55  ; }
			else if (velocity > 2015) { A = 3.222942271262336e-03; M = 1.575 ; }
			else if (velocity > 1890) { A = 2.203329542297809e-03; M = 1.625 ; }
			else if (velocity > 1810) { A = 1.511001028891904e-03; M = 1.675 ; }
			else if (velocity > 1730) { A = 8.609957592468259e-04; M = 1.75  ; }
			else if (velocity > 1595) { A = 4.086146797305117e-04; M = 1.85  ; }
			else if (velocity > 1520) { A = 1.954473210037398e-04; M = 1.95  ; }
			else if (velocity > 1420) { A = 5.431896266462351e-05; M = 2.125 ; }
			else if (velocity > 1360) { A = 8.847742581674416e-06; M = 2.375 ; }
			else if (velocity > 1315) { A = 1.456922328720298e-06; M = 2.625 ; }
			else if (velocity > 1280) { A = 2.419485191895565e-07; M = 2.875 ; }
			else if (velocity > 1220) { A = 1.657956321067612e-08; M = 3.25  ; }
			else if (velocity > 1185) { A = 4.745469537157371e-10; M = 3.75  ; }
			else if (velocity > 1150) { A = 1.379746590025088e-11; M = 4.25  ; }
			else if (velocity > 1100) { A = 4.070157961147882e-13; M = 4.75  ; }
			else if (velocity > 1060) { A = 2.938236954847331e-14; M = 5.125 ; }
			else if (velocity > 1025) { A = 1.228597370774746e-14; M = 5.25  ; }
			else if (velocity >  980) { A = 2.916938264100495e-14; M = 5.125 ; }
			else if (velocity >  945) { A = 3.855099424807451e-13; M = 4.75  ; }
			else if (velocity >  905) { A = 1.185097045689854e-11; M = 4.25  ; }
			else if (velocity >  860) { A = 3.566129470974951e-10; M = 3.75  ; }
			else if (velocity >  810) { A = 1.045513263966272e-08; M = 3.25  ; }
			else if (velocity >  780) { A = 1.291159200846216e-07; M = 2.875 ; }
			else if (velocity >  750) { A = 6.824429329105383e-07; M = 2.625 ; }
			else if (velocity >  700) { A = 3.569169672385163e-06; M = 2.375 ; }
			else if (velocity >  640) { A = 1.839015095899579e-05; M = 2.125 ; }
			else if (velocity >  600) { A = 5.71117468873424e-05 ; M = 1.950 ; }
			else if (velocity >  550) { A = 9.226557091973427e-05; M = 1.875 ; }
			else if (velocity >  250) { A = 9.337991957131389e-05; M = 1.875 ; }
			else if (velocity >  100) { A = 7.225247327590413e-05; M = 1.925 ; }
			else if (velocity >   65) { A = 5.792684957074546e-05; M = 1.975 ; }
			else if (velocity >    0) { A = 5.206214107320588e-05; M = 2.000 ; }
			break;

		case 7:
			if (velocity > 4200 )      { A = 1.29081656775919e-09; M = 3.24121295355962; }
			else if (velocity > 3000 ) { A = 0.0171422231434847  ; M = 1.27907168025204; }
			else if (velocity > 1470 ) { A = 2.33355948302505e-03; M = 1.52693913274526; }
			else if (velocity > 1260 ) { A = 7.97592111627665e-04; M = 1.67688974440324; }
			else if (velocity > 1110 ) { A = 5.71086414289273e-12; M = 4.3212826264889 ; }
			else if (velocity >  960 ) { A = 3.02865108244904e-17; M = 5.99074203776707; }
			else if (velocity >  670 ) { A = 7.52285155782535e-06; M = 2.1738019851075 ; }
			else if (velocity >  540 ) { A = 1.31766281225189e-05; M = 2.08774690257991; }
			else if (velocity >    0 ) { A = 1.34504843776525e-05; M = 2.08702306738884; }
			break;

		case 8:
			if (velocity > 3571 )      { A = .0112263766252305   ; M = 1.33207346655961; }
			else if (velocity > 1841 ) { A = .0167252613732636   ; M = 1.28662041261785; }
			else if (velocity > 1120 ) { A = 2.20172456619625e-03; M = 1.55636358091189; }
			else if (velocity > 1088 ) { A = 2.0538037167098e-16 ; M = 5.80410776994789; }
			else if (velocity >  976 ) { A = 5.92182174254121e-12; M = 4.29275576134191; }
			else if (velocity >    0 ) { A = 4.3917343795117e-05 ; M = 1.99978116283334; }
			break;

		default:
			break;
	}
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
	double time_delta = 1 / initial_velocity;
	double y = -sight_height / 12;
	double x = 0;
	double angular_delta; 		// The change in bore angle used to iterate over to approximate the correct zero angle

	// State variables for each loop
	double t = 0; 				// time in seconds
	double v=0, vx=0, vy=0; 	// velocity variables
	double vx1=0, vy1=0; 		// Last frame's velocity, used for computing average velocity
	double dv=0, dvx=0, dvy=0;  // change in acceleration
	double Gx=0, Gy=0; 			// Gravitational acceleration

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


		for (t = 0, x = 0, y = -sight_height / 12; x <= zero_range*3; t += time_delta)
		{
			vx1 = vx;
			vy1 = vy;
			v = pow((pow(vx,2) + pow(vy,2)), 0.5);
			time_delta = 1 / v;

			double velocity_delta = apply_drag(drag_function, ballistic_coefficient, v);
			dvy = - velocity_delta * vy / v * time_delta;
			dvx = - velocity_delta * vx / v * time_delta;

			vx += dvx;
			vy += dvy;
			vy += time_delta * Gy;
			vx += time_delta * Gx;

			x = x + time_delta * (vx+vx1) / 2;
			y = y + time_delta * (vy+vy1) / 2;

			// Break early to save CPU time if we won't find a solution.
			if (vy < 0 && y < y_intercept) {
				break;
			}
			if (vy > 3 * vx) {
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

std::map<int, RangeData> calculate_range_table(
		int drag_function,
		double ballistic_coefficient,
		double velocity,
		double sight_height,
		double shooting_angle,
		double zero_range,
		double wind_velocity,
		double wind_angle)
{
	map<int, RangeData> range_table;

	double t = 0;
	double delta_time = 0.5 / velocity;
	double v = 0;
	double vx = 0, vx1 = 0, vy = 0, vy1 = 0;
	double dv = 0, dvx = 0, dvy = 0;
	double x = 0, y = 0;

	// Find the zero angle of the bore relative to the sighting system.
	double zero_angle = calculate_zero_angle(drag_function, ballistic_coefficient, velocity,
			sight_height, zero_range, 0);

	double headwind = calculate_headwind(wind_velocity, wind_angle);
	double crosswind = calculate_crosswind(wind_velocity, wind_angle);

	double Gy = GRAVITY * cos(degree_to_radian((shooting_angle + zero_angle)));
	double Gx = GRAVITY * sin(degree_to_radian((shooting_angle + zero_angle)));

	vx = velocity * cos(degree_to_radian(zero_angle));
	vy = velocity * sin(degree_to_radian(zero_angle));

	y = -sight_height / 12;
	int n = 0;
	for ( t = 0 ;; t += delta_time ) // time in seconds + delta each loop
	{
		vx1 = vx, vy1 = vy;
		v = pow(pow(vx, 2) + pow(vy, 2), 0.5);
		delta_time = 0.5 / v;

		dv = apply_drag(drag_function, ballistic_coefficient, v + headwind);
		dvx = -(vx / velocity) * dv;
		dvy = -(vy / velocity) * dv;

		vx = vx + delta_time * dvx + delta_time * Gx;
		vy = vy + delta_time * dvy + delta_time * Gy;

		double yardage = x / 3;

		if (yardage >= n)
		{
			double windage = calculate_windage(crosswind, velocity, x, t + delta_time);

			RangeData data (
					yardage,
				  	y * 12,
				  	-radian_to_moa(atan(y / x)),
				  	t * delta_time,
				  	windage,
					radian_to_moa(atan((windage / 12) / (yardage * 3))),
					velocity,
					vx,
					vy
 					);
 			range_table.insert(make_pair(yardage, data));
			n++;
		}

		x = x + delta_time * (vx + vx1) / 2;
		y = y + delta_time * (vy + vy1) / 2;

		if (fabs(vy) > fabs(3*vx)) break;
		if (n >= __MAXRANGE__+1) break;
	}

	return range_table;
}
