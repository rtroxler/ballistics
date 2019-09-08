#ifndef calc
#define calc
#define __MAXRANGE__ 5000
#define GRAVITY (-32.194)
#include <math.h>
#include <map>
#include "range_data.h"

double apply_drag(int drag_function, double ballistic_coefficient, double velocity);

double calculate_zero_angle(
		int drag_function,
		double ballistic_coefficient,
		double initial_velocity,
		double sight_height,
		double zero_range,
		double y_intercept);

double atmosphere_adjustment(double ballistic_coefficient, double altitude, double barometer, double temp, double relative_humidity);

std::map<int, RangeData> calculate_range_table(
		int drag_function,
		double ballistic_coefficient,
		double velocity,
		double sight_height,
		double shooting_angle,
		double zero_range,
		double wind_velocity,
		double wind_angle
		);
#endif
