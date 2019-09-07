#include <iostream>
#include <map>
#include "calc.h"
#include "conversions.h"
#include "range_data.h"

using namespace std;

void print_data_at_range(map<int, RangeData> range_table, int yardage)
{
	double moa_adjustment = range_table[yardage].get_moa_correction();
	double windage_adjustment = range_table[yardage].get_windage_correction();

	cout << yardage << " yd: " << "\t" << fixed << moa_adjustment << "\t\t" << windage_adjustment << endl;
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
	double wind_angle = 90; 					// Wind Angle (0-360 degrees)
	double wind_velocity = 10.0;

	// No atmospheric adjustments rn

	cout.precision(2);

	map<int, RangeData> range_table = calculate_range_table(drag_function, ballistic_coefficient, velocity, sight_height, shooting_angle, zero_range, wind_velocity, wind_angle);

	cout << "\nYardage | MOA Adjustment | Windage" << endl;
	for (int i = 100; i <= 1000; i += 100)
	{
		print_data_at_range(range_table, i);
	}
}
