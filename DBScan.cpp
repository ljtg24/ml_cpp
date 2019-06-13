#include<iostream>  
#include<cstring>  
#include<cctype>
#include<math.h>
#include<vector>
#include<map>
#include<deque>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string>
using namespace std;  

const int NOISE = -3;
const int NOT_CLASSIFIED = -2;
const int WAIT_CLASSIFIED = -1;
typedef map<int, vector<int>> pts_in_kernel_eps;
// typedef vector<pts_in_kernel_eps> kernels_info;
bool eleInDeque(deque<int> dd, int ele);


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

DBScan::DBScan(int minPts, double Eps, vector<Point> points)
{
    this->minPts = minPts;
    this->Eps = Eps;
    this->points = points;
    this->init_mode = brute;
    this->n_clusters_ = -1;

    this->data_size = (int)points.size();
    this->dims = (int)points[0].p_value.size();

    // for (int i = 0; i < data_size; i++){
    //     labels_[i] = n_clusters_;
    // }
}

DBScan::~DBScan()
{}

void DBScan::dbscan()
{
    // kernels_info kns_info;
    pts_in_kernel_eps pts_in_eps;
    // pts_in_kernel_eps temp_pts_in_eps;
    for (int i = 0; i < data_size; i++)
    {
        vector<int> temp_pts;
        int pts_statistic = 0;
        for (int j = 0; j < data_size; j++)
        {
            if (i == j)
                continue;
            if (points[i].caculate_dis(points[j], dims) <= Eps){
                ++pts_statistic;
                //decrease Repeated storage
                if (points[j].cluster != WAIT_CLASSIFIED)  
                    temp_pts.push_back(j);
            }
                
        }
        
        if (pts_statistic >= minPts)
        {
            // change cluster of point in temp_pts to WAIT_CLASSIFIED
            for (auto i: temp_pts)
            {
                points[i].cluster = WAIT_CLASSIFIED;
            } 
            // add kernel point index into vector(kernel_point_idx)
            kernel_points_idx.push_back(i);
            pts_in_eps[i] = temp_pts;
            // temp_pts_in_eps.insert(make_pair(i, temp_pts));
            // add kernel point index and the index of points in the Eps of kernel point
            // kns_info.push_back(temp_pts_in_eps);
            // temp_pts_in_eps.clear();
        }
        
    }
    // combine the adjacent kernel points
    // vector<vector<int>> adjacent_kernels_idx;
    deque<int> d1;
    // initial cluster of first kernel point 
    // points[kernel_points_idx[0]].cluster = cluster+1;
    int kernel_pts_num = kernel_points_idx.size();
    // coding will be simple if use method auto of vector, but... 
    for (int i = 0; i < kernel_pts_num; i++)
    {   
        int i_idx = kernel_points_idx[i];
        if (points[i_idx].cluster < 0)
        {
            d1.push_back(i);
            ++n_clusters_;
              // cluster number start with 0
            points[i_idx].cluster = n_clusters_;
        }
        while(d1.size() > 0)
        {
            int temp_i = d1.front();
            d1.pop_front();
            for (int j = i+1; j < kernel_pts_num; j++)
            {
                if (i == j)
                    continue;
                int temp_idx = kernel_points_idx[temp_i];
                int j_idx = kernel_points_idx[j];
                if (points[j_idx].cluster<0 and points[temp_idx].caculate_dis(points[j_idx], dims) <= Eps)
                {
                    points[j_idx].cluster = n_clusters_;
                    if (!eleInDeque(d1, j))
                        d1.push_back(j);
                }
            }
        }
        
    }
    // assign cluster
    for (pts_in_kernel_eps::iterator iter = pts_in_eps.begin(); iter != pts_in_eps.end(); iter++)
    {
        int idx = iter->first;
        int cluster = points[idx].cluster;
        for (auto i: iter->second)
        {   points[i].cluster = cluster;}    
    }
    for (auto p: points)
    {
        labels_.push_back(p.cluster);
    }
}

bool eleInDeque(deque<int> dd, int ele)
{
    for (auto idx: dd){
        if (idx == ele)
            return true;
    }
    return false;
}

int main()
{
    double data[30] = {
        1,2,3,
        1,2,2,
        2,2,3,
        2000,3000,1000,
        40.9,40.9,40.9,
        40,40,45,
        40,39,39,
        100,100,100,
        100,101,99,
        101,100,101
    };
    int data_len = 30;
    vector<Point> points;
    for (int i = 0; i<data_len-2; i=i+3)
    {
        // Point p;
        vector<double> point;
        point.push_back(data[i]);
        point.push_back(data[i+1]);
        point.push_back(data[i+2]);
        // p.p_value = point;
        // p.cluster = NOT_CLASSIFIED;
        points.push_back({point, NOT_CLASSIFIED});
    }
    std::cout<<points.size() << "  " << points[0].cluster << " " <<endl;
    for (auto i : points[0].p_value){
        cout << i;
    }
    cout << endl;
    DBScan dbs(2, 10.0, points);
    dbs.dbscan();
    return 0;
}
