#include<iostream>  
#include<cstring>  
#include<cctype>
#include<math.h>
#include<vector> 
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string>
using namespace std;  

const int NOISE = -2;
const int NOT_CLASSIFIED = -1;

class Point
{
public:
    vector<double> p_value;
    int cluster;

    double caculate_dis(const Point& pt, int dims);
};

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

class DBScan
{
private:
    vector<Point> points;
    int minPts;
	double Eps; 
    vector<int> labels_;
    int n_clusters_;
    int init_mode;

    int dims;
    int data_size;
    vector<int> kernel_points_idx;
public:
    enum initMode
    {
		brute,
        kd_tree,
        ball_tree,
    };
    DBScan(int minPts, double Eps, vector<Point> points);
    ~DBScan();

    void dbscan();
    // void get_label(const double* pt, int* label);

};

DBScan::DBScan(int minPts=1, double Eps=1.0, vector<Point> points)
{
    this->minPts = minPts;
    this->Eps = Eps;
    this->init_mode = brute;
    this->n_clusters_ = -1;

    this->data_size = (int)points.size();
    this->dims = (int)points[0].p_value.size();

    for (int i = 0; i < data_size; i++){
        labels_[i] = n_clusters_;
    }
}

DBScan::~DBScan()
{}

void DBScan::dbscan()
{
    for (int i = 0; i < data_size; i++)
    {
        int adjacent_pt_num = 0;
        for (int j = 0; j < data_size; j++)
        {
            if (i == j)
                continue;
            if (points[i].caculate_dis(points[j], dims) < Eps)
                adjacent_pt_num++;
        }
        // add kernel point index into vector(kernel_point_idx)
        if (adjacent_pt_num >= minPts)
            kernel_points_idx.push_back(i);
        // combine the adjacent kernel points
        vector<vector<int>> adjacent_kernels_idx;
        for (auto i : kernel_points_idx)
        {   
            vector<int> temp_adjacent;
            for (auto j : kernel_points_idx)
            {
                if (i == j)
                    continue;
                if (points[i].caculate_dis(points[j], dims) < Eps)
                    temp_adjacent.push_back(j);
            }
        }
    }
}

