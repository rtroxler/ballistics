#include <iostream>
#include <map>
#include "calc.h"
#include "conversions.h"
#include "range_data.h"

using namespace std;
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

	// Find the zero angle of the bore relative to the sighting systme.
	double zero_angle = calculate_zero_angle(drag_function, ballistic_coefficient, velocity, sight_height, zero_range, 0);

	map<int, RangeData> range_table;
	int num_rows = compute_range_table(drag_function, ballistic_coefficient, velocity, sight_height, shooting_angle,
										zero_angle, wind_velocity, wind_angle, range_table);

	cout << "Let's shoot some shit.\n";
	cout << "zero angle: " << fixed << zero_angle << endl;
	cout << "\nYardage | MOA Adjustment | Windage" << endl;
	cout << "100 yd: " << "\t" << range_table[100].get_moa_correction() << "\t\t" << range_table[100].get_windage_correction() << endl;
	cout << "200 yd: " << "\t" << range_table[200].get_moa_correction() << "\t\t" << range_table[200].get_windage_correction() << endl;
	cout << "300 yd: " << "\t" << range_table[300].get_moa_correction() << "\t\t" << range_table[300].get_windage_correction() << endl;
	cout << "400 yd: " << "\t" << range_table[400].get_moa_correction() << "\t\t" << range_table[400].get_windage_correction() << endl;
	cout << "500 yd: " << "\t" << range_table[500].get_moa_correction() << "\t\t" << range_table[500].get_windage_correction() << endl;
	cout << "600 yd: " << "\t" << range_table[600].get_moa_correction() << "\t\t" << range_table[600].get_windage_correction() << endl;
	cout << "700 yd: " << "\t" << range_table[700].get_moa_correction() << "\t\t" << range_table[700].get_windage_correction() << endl;
	cout << "800 yd: " << "\t" << range_table[800].get_moa_correction() << "\t\t" << range_table[800].get_windage_correction() << endl;
	cout << "900 yd: " << "\t" << range_table[900].get_moa_correction() << "\t\t" << range_table[900].get_windage_correction() << endl;
	cout << "1000 yd: " << "\t" << range_table[1000].get_moa_correction() << "\t\t" << range_table[1000].get_windage_correction() << endl;
}
