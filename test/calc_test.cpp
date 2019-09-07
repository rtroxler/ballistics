#define BOOST_TEST_MODULE Hello
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include "../src/calc.h"

namespace utf = boost::unit_test;
namespace tt = boost::test_tools;

using namespace std;

void assert_equal(double a, double b, double tolerance = 0.0001)
{
    BOOST_TEST(a == b, tt::tolerance(tolerance));
}


/// zero angle tests
BOOST_AUTO_TEST_CASE(zero_angle_G7_2650_200, * utf::tolerance(0.0001))
{
	int drag_function = 7; // G7
	double ballistic_coefficient = 0.465; // Ballistics Coefficient
	double velocity = 2650; // Initial muzzle velocity
	double sight_height = 1.6; // Sight height over bore in inches
	double zero_range = 200; // Zero range (yards)

	double zero_angle = calculate_zero_angle(drag_function, ballistic_coefficient, velocity, sight_height, zero_range, 0);

	cout << "zero angle: " << fixed << zero_angle << endl;
    assert_equal(zero_angle, 0.095596);
}

BOOST_AUTO_TEST_CASE(zero_angle_G7_2650_100, * utf::tolerance(0.0001))
{
	int drag_function = 7; // G7
	double ballistic_coefficient = 0.465; // Ballistics Coefficient
	double velocity = 2650; // Initial muzzle velocity
	double sight_height = 1.6; // Sight height over bore in inches
	double zero_range = 100; // Zero range (yards)

	double zero_angle = calculate_zero_angle(drag_function, ballistic_coefficient, velocity, sight_height, zero_range, 0);

	cout << "zero angle: " << fixed << zero_angle << endl;
    assert_equal(zero_angle, 0.065903);
}

BOOST_AUTO_TEST_CASE(zero_angle_G7_2800_100_0365, * utf::tolerance(0.0001))
{
	int drag_function = 7; // G7
	double ballistic_coefficient = 0.365; // Ballistics Coefficient
	double velocity = 2800; // Initial muzzle velocity
	double sight_height = 1.6; // Sight height over bore in inches
	double zero_range = 100; // Zero range (yards)

	double zero_angle = calculate_zero_angle(drag_function, ballistic_coefficient, velocity, sight_height, zero_range, 0);

	cout << "zero angle: " << fixed << zero_angle << endl;
    assert_equal(zero_angle, 0.061844);
}

/// apply drag
BOOST_AUTO_TEST_CASE(apply_drag_g7_365, * utf::tolerance(0.0001))
{
	int drag_function = 7; // G7
	double ballistic_coefficient = 0.365; // Ballistics Coefficient
	double velocity = 2800; // Initial muzzle velocity

	double velocity_delta = apply_drag(drag_function, ballistic_coefficient, velocity);

	cout << "velocity_delta: " << fixed << velocity_delta << endl;
	assert_equal(velocity_delta, 1173.0769);
}

BOOST_AUTO_TEST_CASE(apply_drag_g7_465, * utf::tolerance(0.0001))
{
	int drag_function = 7; // G7
	double ballistic_coefficient = 0.465; // Ballistics Coefficient
	double velocity = 2800; // Initial muzzle velocity

	double velocity_delta = apply_drag(drag_function, ballistic_coefficient, velocity);

	cout << "velocity_delta: " << fixed << velocity_delta << endl;
	assert_equal(velocity_delta, 920.8023);
}

BOOST_AUTO_TEST_CASE(apply_drag_g7_565, * utf::tolerance(0.0001))
{
	int drag_function = 7; // G7
	double ballistic_coefficient = 0.565; // Ballistics Coefficient
	double velocity = 2800; // Initial muzzle velocity

	double velocity_delta = apply_drag(drag_function, ballistic_coefficient, velocity);

	cout << "velocity_delta: " << fixed << velocity_delta << endl;
	assert_equal(velocity_delta, 757.8284);
}

BOOST_AUTO_TEST_CASE(apply_drag_g7_365_2900, * utf::tolerance(0.0001))
{
	int drag_function = 7; // G7
	double ballistic_coefficient = 0.365; // Ballistics Coefficient
	double velocity = 2900; // Initial muzzle velocity

	double velocity_delta = apply_drag(drag_function, ballistic_coefficient, velocity);

	cout << "velocity_delta: " << fixed << velocity_delta << endl;
	assert_equal(velocity_delta, 1237.6476, 0.001);
}

BOOST_AUTO_TEST_CASE(apply_drag_g7_565_3000, * utf::tolerance(0.0001))
{
	int drag_function = 7; // G7
	double ballistic_coefficient = 0.565; // Ballistics Coefficient
	double velocity = 3000; // Initial muzzle velocity

	double velocity_delta = apply_drag(drag_function, ballistic_coefficient, velocity);

	cout << "velocity_delta: " << fixed << velocity_delta << endl;
	assert_equal(velocity_delta, 842.0210);
}

/// calculate range table
BOOST_AUTO_TEST_CASE(range_table_365_2650, * utf::tolerance(0.0001))
{
	int drag_function = 7; 					// G7
	double ballistic_coefficient = 0.365;
	double velocity = 2650; 				// Initial muzzle velocity
	double zero_range = 100; 				// Zero range (yards)
	double sight_height = 1.6; 				// Sight height over bore in inches
	double shooting_angle = 0;  			// angle from X in degrees
	double wind_angle = 90; 					// Wind Angle (0-360 degrees)
	double wind_velocity = 10.0;

	cout << "MOA adjustments for 0.365 / 2650 / G7";
	map<int, RangeData> range_table = calculate_range_table(drag_function, ballistic_coefficient, velocity, sight_height, shooting_angle, zero_range, wind_velocity, wind_angle);
	cout << "moa adj at 100: " << range_table[100].get_moa_correction() << endl;
	cout << "moa adj at 200: " << range_table[200].get_moa_correction() << endl;
	cout << "moa adj at 300: " << range_table[300].get_moa_correction() << endl;
	cout << "moa adj at 500: " << range_table[500].get_moa_correction() << endl;
	cout << "moa adj at 1000: " << range_table[1000].get_moa_correction() << endl;
	assert_equal(range_table[100].get_moa_correction(), 0.00, 0.001);
	assert_equal(range_table[200].get_moa_correction(), 1.829, 0.001);
	assert_equal(range_table[300].get_moa_correction(), 4.326, 0.001);
	assert_equal(range_table[500].get_moa_correction(), 10.14);
	assert_equal(range_table[1000].get_moa_correction(), 28.435);
}

BOOST_AUTO_TEST_CASE(range_table_465_2650, * utf::tolerance(0.0001))
{
	int drag_function = 7; 					// G7
	double ballistic_coefficient = 0.465;
	double velocity = 2650; 				// Initial muzzle velocity
	double zero_range = 100; 				// Zero range (yards)
	double sight_height = 1.6; 				// Sight height over bore in inches
	double shooting_angle = 0;  			// angle from X in degrees
	double wind_angle = 90; 					// Wind Angle (0-360 degrees)
	double wind_velocity = 10.0;

	cout << "MOA adjustments for 0.465 / 2650 / G7";
	map<int, RangeData> range_table = calculate_range_table(drag_function, ballistic_coefficient, velocity, sight_height, shooting_angle, zero_range, wind_velocity, wind_angle);
	cout << "moa adj at 100: " << range_table[100].get_moa_correction() << endl;
	cout << "moa adj at 200: " << range_table[200].get_moa_correction() << endl;
	cout << "moa adj at 300: " << range_table[300].get_moa_correction() << endl;
	cout << "moa adj at 500: " << range_table[500].get_moa_correction() << endl;
	cout << "moa adj at 1000: " << range_table[1000].get_moa_correction() << endl;
	assert_equal(range_table[100].get_moa_correction(), 0.00, 0.01);
	assert_equal(range_table[200].get_moa_correction(), 1.7756, 0.001);
	assert_equal(range_table[300].get_moa_correction(), 4.1853, 0.001);
	assert_equal(range_table[500].get_moa_correction(), 9.6994);
	assert_equal(range_table[1000].get_moa_correction(), 26.3557);
}

BOOST_AUTO_TEST_CASE(range_table_365_2900, * utf::tolerance(0.0001))
{
	int drag_function = 7; 					// G7
	double ballistic_coefficient = 0.365;
	double velocity = 2900; 				// Initial muzzle velocity
	double zero_range = 100; 				// Zero range (yards)
	double sight_height = 1.6; 				// Sight height over bore in inches
	double shooting_angle = 0;  			// angle from X in degrees
	double wind_angle = 90; 					// Wind Angle (0-360 degrees)
	double wind_velocity = 10.0;

	cout << "MOA adjustments for 0.465 / 2650 / G7";
	map<int, RangeData> range_table = calculate_range_table(drag_function, ballistic_coefficient, velocity, sight_height, shooting_angle, zero_range, wind_velocity, wind_angle);
	cout << "moa adj at 100: " << range_table[100].get_moa_correction() << endl;
	cout << "moa adj at 200: " << range_table[200].get_moa_correction() << endl;
	cout << "moa adj at 300: " << range_table[300].get_moa_correction() << endl;
	cout << "moa adj at 500: " << range_table[500].get_moa_correction() << endl;
	cout << "moa adj at 1000: " << range_table[1000].get_moa_correction() << endl;
	assert_equal(range_table[100].get_moa_correction(), 0.00, 0.01);
	assert_equal(range_table[200].get_moa_correction(), 1.385, 0.001);
	assert_equal(range_table[300].get_moa_correction(), 3.414, 0.001);
	assert_equal(range_table[500].get_moa_correction(), 8.185, 0.001);
	assert_equal(range_table[1000].get_moa_correction(), 23.1641, 0.001);
}
