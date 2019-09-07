#include "range_data.h"
RangeData::RangeData(int range, // this constructor is nuts
		double y_path,
		double moa_correction,
		double flight_time,
		double windage_inches,
		double windage_moa,
		double velocity,
		double velocity_x,
		double velocity_y) : range(range), y_path(y_path), moa_correction(moa_correction), flight_time(flight_time),
	windage_inches(windage_inches), windage_moa(windage_moa), velocity(velocity),
	velocity_x(velocity_x), velocity_y(velocity_y)
{}
RangeData::RangeData() {}

double RangeData::get_moa_correction()
{
	return moa_correction;
}

double RangeData::get_windage_correction()
{
	return windage_moa;
}
