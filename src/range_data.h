#ifndef RANGE_DATA_H
#define RANGE_DATA_H
class RangeData
{
	private:
	int range;		// in yards
	double y_path,
		   moa_correction,
		   flight_time,
		   windage_inches,
		   windage_moa,
		   velocity,
		   velocity_x,
		   velocity_y;
	public:
	RangeData(int range, // this constructor is nuts
			double y_path,
			double moa_correction,
			double flight_time,
			double windage_inches,
			double windage_moa,
			double velocity,
			double velocity_x,
			double velocity_y);
	RangeData();

	double get_moa_correction();
	double get_windage_correction();
};
#endif
