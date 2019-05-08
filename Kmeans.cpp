// reference from https://github.com/luxiaoxun/KMeans-GMM-HMM/

#include<iostream>  
#include<cstring>  
#include<cctype>
#include<math.h>
#include<vector> 
#include<ctime> 
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<random>
#include<string>
using namespace std;  

double caculate_dis(const double* x, const double* y, int dims);

class KMeans
{
private:
    int k;
    int dims;
    double** mean_cts;
    int max_iters;
    double end_errors;
    int init_mode;

public:
    enum initMode
    {
        init_random,
        init_uniform,
    };
    KMeans(int k=1, int dims=1);
    ~KMeans();

    void set_meanCt(int i, const double* x){memcpy(mean_cts[i], x, sizeof(double)*dims);};
    void set_maxIter(int i){max_iters=i;};
    void set_initMode(int i){init_mode=i;};
    void set_endError(double d){end_errors=d;};

    double* get_meanCt(int i){return mean_cts[i];};
    int get_initMode(){return init_mode;};

    void kmeans(double *datas, int N, int *labels);
    void get_label(const double* pt, int* label);
    void Init(double *datas, int N);

};

KMeans::KMeans(int k_, int dims_)
{
    k = k_;
    dims = dims_;
    mean_cts = new double* [k];
    for (int i=0; i < k; i++)
    {
        mean_cts[i] = new double [dims];
        memset(mean_cts[i], 0.0, sizeof(double)*dims);
    }
    max_iters = 100;
    end_errors = 0.001;
    init_mode = init_random;
}

KMeans::~KMeans()
{
    for (int i = 0; i < k; i++)
    {
        delete[] mean_cts[i];
    }
    delete[] mean_cts;
}

void KMeans::Init(double *datas, int N)
{
    int size=N;
    if (init_mode == init_random)
    {
        double* sample = new double[dims];
        default_random_engine e(time(NULL));
        uniform_int_distribution<unsigned> u(0, size-1);
        for(int i=0; i<k; i++){
            int sample_ind = u(e);
            for (int j = 0; j < dims; j++){
                sample[j] = datas[sample_ind*dims+j];
                memcpy(mean_cts[i], sample, sizeof(double)*dims);
            }
        }
        delete[] sample;
    }
    else if(init_mode == init_uniform)
    {
        //not implement
    } 
    else
    {
        //not implement
    }
}

void KMeans::kmeans(double *datas, int N, int *labels)
{
    int size = N;
    assert(nullptr != datas);

    assert(size >= k);
    Init(datas, size);

    int iter_num = 0;
    bool flag = true;
    int label = -1;
    double* pt = new double [dims];
    int* pt_count = new int[k];

    double** post_mean_cts = new double*[k];
    for (int i = 0; i < k; i++)
    {
        post_mean_cts[i] = new double [dims];
    }

    while (flag){
        double all_cts_distance_changed = 0;
        memset(pt_count, 0, sizeof(int)*k);

        for (int i = 0; i < k; i++)
            memset(post_mean_cts[i], 0.0, sizeof(double)*dims);
        //caculate new centers
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < dims; j++)
            {
                pt[j] = datas[i*dims+j];
            }
                
            get_label(pt, &label);
            pt_count[label]++;
            for (int j = 0; j < dims; j++)
            {
                post_mean_cts[label][j] += pt[j]; // whether post_mean_cts[label][j] be overflow
            }
        }

        for (int i = 0; i < k; i++)
        {
            int pt_count_i = pt_count[i];
            for (int j = 0; j < dims; j++)
            {
                post_mean_cts[i][j] /= pt_count_i;
            }
            all_cts_distance_changed += caculate_dis(mean_cts[i], post_mean_cts[i], dims);
            // update centers
            memcpy(mean_cts[i], post_mean_cts[i], sizeof(double)*dims);
        }
        
        iter_num++;
        if (iter_num >= max_iters || all_cts_distance_changed < end_errors){
            flag = false;
        }
    }
    // get labels
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < dims; j++)
            pt[j] = datas[i*dims+j];
        
        get_label(pt, &label);
        labels[i] = label;
    }

    // delete object created by new method
    delete[] pt;
    delete[] pt_count;
    for (int i = 0; i < k; i++)
    {
        delete[] post_mean_cts[i];
    }
    delete[] post_mean_cts;

}
void KMeans::get_label(const double* pt, int* label)
{
    double min_dis = -1;
    for (int j = 0; j < k; j++)
    {
        double temp = caculate_dis(pt, mean_cts[j], dims);
        if (temp < min_dis || min_dis == -1)
        {
            min_dis = temp;
            *label = j;
        }
    }
}
double caculate_dis(const double* x, const double* y, int dims)
{
    double distance = 0.0;
    for (int i = 0; i < dims; i++)
    {
        distance += pow((x[i] - y[i]), 2);
    }
    distance = sqrt(distance);

    return distance;
}


int main()  
{   
    const int N = 10;
    double *p;
    double data[] = {
        1,2,3,
        1,2,2,
        2,2,3,
        2,3,1,
        4.9,4.9,4.9,
        4,4,5,
        4,3,3,
        10,10,10,
        10,11,9,
        11,10,11
    };
    // cout << sizeof(data) << endl;
    p = data;
    int* labels = new int[N];
    memset(labels, 0, sizeof(int)*N);
    KMeans* km = new KMeans(3,3);
    km->kmeans(p, 10, labels);
    for (int i = 0; i < N; i++)
    {
        cout << labels[i] << ": " << data[i*3] << "," << data[i*3+1] << "," << data[i*3+2] << '\n';
    }

    return 0;  
}
