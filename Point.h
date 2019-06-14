#include<map>
#include<vector>
#include<math.h>
using namespace std;
const int NOISE = -3;
const int NOT_CLASSIFIED = -2;
const int WAIT_CLASSIFIED = -1;


class Point
{
public:
    vector<double> p_value;
    int cluster;
    double caculate_dis(const Point& pt, int dims);
};