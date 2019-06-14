#include "Point.h"
// typedef vector<pts_in_kernel_eps> kernels_info;

double Point::caculate_dis(const Point& pt, int dims)
{
    double distance = 0.0;
    for (int i = 0; i < dims; i++)
    {
        distance += pow((p_value[i] - pt.p_value[i]), 2);
    }
    distance = sqrt(distance);

    return distance;
}