#define BOOST_TEST_MODULE Hello
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include "../src/calc.h"

namespace utf = boost::unit_test;
namespace tt = boost::test_tools;

using namespace std;

BOOST_AUTO_TEST_CASE(zero_angle_G7_2650_200, * utf::tolerance(0.0001))
{
	int drag_function = 7; // G7
	double drag_coefficient = 0.465; // Ballistics Coefficient
	double velocity = 2650; // Initial muzzle velocity
	double sight_height = 1.6; // Sight height over bore in inches
	double zero_range = 200; // Zero range (yards)

	double zero_angle = calculate_zero_angle(drag_function, drag_coefficient, velocity, sight_height, zero_range, 0);

	cout << "zero angle: " << fixed << zero_angle << endl;
    BOOST_TEST(zero_angle == 0.095596, tt::tolerance(0.0001));
}

BOOST_AUTO_TEST_CASE(zero_angle_G7_2650_100, * utf::tolerance(0.0001))
{
	int drag_function = 7; // G7
	double drag_coefficient = 0.465; // Ballistics Coefficient
	double velocity = 2650; // Initial muzzle velocity
	double sight_height = 1.6; // Sight height over bore in inches
	double zero_range = 100; // Zero range (yards)

	double zero_angle = calculate_zero_angle(drag_function, drag_coefficient, velocity, sight_height, zero_range, 0);

	cout << "zero angle: " << fixed << zero_angle << endl;
    BOOST_TEST(zero_angle == 0.065903, tt::tolerance(0.0001));
}

BOOST_AUTO_TEST_CASE(zero_angle_G7_2800_100_0365, * utf::tolerance(0.0001))
{
	int drag_function = 7; // G7
	double drag_coefficient = 0.365; // Ballistics Coefficient
	double velocity = 2800; // Initial muzzle velocity
	double sight_height = 1.6; // Sight height over bore in inches
	double zero_range = 100; // Zero range (yards)

	double zero_angle = calculate_zero_angle(drag_function, drag_coefficient, velocity, sight_height, zero_range, 0);

	cout << "zero angle: " << fixed << zero_angle << endl;
    BOOST_TEST(zero_angle == 0.061844, tt::tolerance(0.0001));
}
