#include<iostream>
#include<math.h>
#include "Meanshift.h"
using namespace std;

double caculate_dis(Point x, Point y)
{
    int dims = x.size();
    double distance = 0.0;
    for (int i = 0; i < dims; i++)
    {
        distance += pow((x[i] - y[i]), 2);
    }
    distance = sqrt(distance);

    return distance;
}

double gaussian_kernel(double distance, double kernel_bandwidth){
    double temp =  exp(-1.0/2.0 * (distance*distance) / (kernel_bandwidth*kernel_bandwidth));
    return temp;
}

MeanShift::MeanShift(double bandwith, int kernel, vector<Point> pointss)
{
    this->bandwith = bandwith;
    this->kernel = kernel;
    this->points = pointss;
}

MeanShift::~MeanShift()
{}

void MeanShift::init_kernel()
{
    if (kernel == gauss_kernel)
    {
        kernel_func=gaussian_kernel;
    }
    else
    {
        throw "Not Implement!";
    }
    
}

void MeanShift::run()
{
    // init kernel function
    init_kernel();
    const double stop_eps = bandwith*0.001;
    int iter_num = 0;
    double shifted_dis = INT64_MAX;
    vector<bool> shift_status;
    for (int i = 0; i < points.size(); i++)
        shift_status[i] = false;
    
    while (shifted_dis < stop_eps and iter_num < MAX_ITER)
    {

        
        ++iter_num;
    }
}