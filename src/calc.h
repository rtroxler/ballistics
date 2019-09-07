#ifndef calc
#define calc
#define __BCOMP_MAXRANGE__ 50001
#define GRAVITY (-32.194)
#include <math.h>

double apply_drag(int drag_function, double ballistic_coefficient, double velocity);

double calculate_zero_angle(
		int drag_function,
		double ballistic_coefficient,
		double initial_velocity,
		double sight_height,
		double zero_range,
		double y_intercept);

double atmosphere_adjustment(double ballistic_coefficient, double altitude, double barometer, double temp, double relative_humidity);

int compute_range_table(
		int drag_function,
		double ballistic_coefficient,
		double velocity,
		double sight_height,
		double shooting_angle,
		double zero_angle,
		double wind_velocity,
		double wind_angle,
		double** table
		);
#endif
