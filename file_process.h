#include<iostream>
#include<string>
using namespace std;

class InputReader {
private:
    ifstream fin;
    // vector<Point> points;
public:
    InputReader(string filename); 
    void parse(); 
    vector<Point> getPoints();
};

// class OutputPrinter {
// private:
//     ofstream fout;
//     vector<vector<int> > cluster;
//     string filename;
//     int n;
// public:
//     OutputPrinter(int n, string filename, vector<vector<int> > cluster) {
//         this->n = n;
//         this->cluster = cluster;
        
//         // remove ".txt" from filename
//         if(filename.size()<4){
//             cout << filename << "input file name's format is wrong\n";
//             exit(0);
//         }
//         for(int i=0;i<4;i++) filename.pop_back();
//         this->filename = filename;
        
//         // sort by size decending order
//         sort(cluster.begin(), cluster.end(), [&](const vector<int> i, const vector<int> j) {
//             return (int)i.size() > (int)j.size();
//         });
//     }
//     void print() {
//         for(int i=0;i<n;i++) {
//             fout.open(filename+"_cluster_"+to_string(i)+".txt");
            
//             for(int j=0;j<cluster[i].size();j++) {
//                 fout << cluster[i][j] << endl;
//             }
            
//             fout.close();
//         }
//     }
// };