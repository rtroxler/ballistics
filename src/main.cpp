#include <iostream>
#include "calc.h"
#include "conversions.h"
using namespace std;

double GetRange(double* sln, int yardage){
	double size=sln[__BCOMP_MAXRANGE__*10+1];
	if (yardage<size){
		return sln[10*yardage];
	}
	else return 0;
}

double GetPath(double* sln, int yardage){
	double size=sln[__BCOMP_MAXRANGE__*10+1];
	if (yardage<size){
		return sln[10*yardage+1];
	}
	else return 0;
}

double GetMOA(double* sln, int yardage){
	double size=sln[__BCOMP_MAXRANGE__*10+1];
	if (yardage<size){
		return sln[10*yardage+2];
	}
	else return 0;
}


double GetTime(double* sln, int yardage){
	double size=sln[__BCOMP_MAXRANGE__*10+1];
	if (yardage<size){
		return sln[10*yardage+3];
	}
	else return 0;
}

double GetWindage(double* sln, int yardage){
	double size=sln[__BCOMP_MAXRANGE__*10+1];
	if (yardage<size){
		return sln[10*yardage+4];
	}
	else return 0;
}

double GetWindageMOA(double* sln, int yardage){
	double size=sln[__BCOMP_MAXRANGE__*10+1];
	if (yardage<size){
		return sln[10*yardage+5];
	}
	else return 0;
}

double GetVelocity(double* sln, int yardage){
	double size=sln[__BCOMP_MAXRANGE__*10+1];
	if (yardage<size){
		return sln[10*yardage+6];
	}
	else return 0;
}

double GetVx(double* sln, int yardage){
	double size=sln[__BCOMP_MAXRANGE__*10+1];
	if (yardage<size){
		return sln[10*yardage+7];
	}
	else return 0;
}

double GetVy(double* sln, int yardage){
	double size=sln[__BCOMP_MAXRANGE__*10+1];
	if (yardage<size){
		return sln[10*yardage+8];
	}
	else return 0;
}

int main()
{
	// Hard code some examples for now
	int drag_function = 7; 					// G7
	double ballistic_coefficient = 0.465;
	double velocity = 2650; 				// Initial muzzle velocity
	double zero_range = 100; 				// Zero range (yards)
	double sight_height = 1.6; 				// Sight height over bore in inches
	double shooting_angle = 0;  			// angle from X in degrees
	double wind_angle = 0; 					// Wind Angle (0-360 degrees)
	double wind_velocity = 0;

	// No atmospheric adjustments rn

	cout.precision(2);

	// Find the zero angle of the bore relative to the sighting systme.
	double zero_angle = calculate_zero_angle(drag_function, ballistic_coefficient, velocity, sight_height, zero_range, 0);

	double* table = NULL;
	int num_rows = compute_range_table(drag_function, ballistic_coefficient, velocity, sight_height, shooting_angle,
										zero_angle, wind_velocity, wind_angle, &(table));

	cout << "Let's shoot some shit.\n";
	cout << "zero angle: " << fixed << zero_angle << endl;
	cout << "\nYardage | MOA Adjustment" << endl;
	cout << " 100 yd: " << GetMOA(table, 100) << endl;
	cout << " 200 yd: " << GetMOA(table, 200) << endl;
	cout << " 300 yd: " << GetMOA(table, 300) << endl;
	cout << " 400 yd: " << GetMOA(table, 400) << endl;
	cout << " 500 yd: " << GetMOA(table, 500) << endl;
	cout << " 600 yd: " << GetMOA(table, 600) << endl;
	cout << " 700 yd: " << GetMOA(table, 700) << endl;
	cout << " 800 yd: " << GetMOA(table, 800) << endl;
	cout << " 900 yd: " << GetMOA(table, 900) << endl;
	cout << "1000 yd: " << GetMOA(table, 1000) << endl;
}
