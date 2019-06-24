#pragma once 

#include<vector> 
typedef vector<double> Point;
#define MAX_ITER 300 

class MeanShift
{
private:
    double bandwith;
    vector<Point> points;
    int n_clusters_;
    vector<int> labels_;
    int kernel;
    
public:
    // enum seed_point, enum find_func(brute, tree)
    enum kernel_func
    {
        gauss_kernel // default
    };
    MeanShift(double bandwith, int kernel, vector<Point> pointss);
    ~MeanShift();
    vector<int> get_labels(){return labels_;};
    int get_cls_num(){return n_clusters_;};
    double (*kernel_func)(double,double);
    void init_kernel();
    void run();
};