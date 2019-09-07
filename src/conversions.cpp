#include "conversions.h"

double degree_to_radian(double degree)
{
	return degree * M_PI / 180;
}
double degree_to_moa(double degree)
{
	return degree * 60;
}

double moa_to_degree(double moa)
{
	return moa / 60;
}
double moa_to_radian(double moa)
{
	return moa / 60 * M_PI / 180;
}

double radian_to_degree(double radian)
{
	return radian * 180.0 / M_PI;
}
double radian_to_moa(double radian)
{
	return radian * 60 * 180 / M_PI;
}
