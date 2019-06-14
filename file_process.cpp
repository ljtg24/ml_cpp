class InputReader {
private:
    ifstream fin;
    vector<Point> points;
public:
    InputReader(string filename) {
        fin.open(filename);
        if(!fin) {
            cout << filename << " file could not be opened\n";
            exit(0);
        }
        parse();
    }
    void parse() {
        int idx;
        double x, y;
        while(!fin.eof()) {
            fin >> idx >> x >> y;
            points.push_back({x,y,0, NOT_CLASSIFIED});
        }
        points.pop_back();
    }
    vector<Point> getPoints() {
        return points;
    }
};

class OutputPrinter {
private:
    ofstream fout;
    vector<vector<int> > cluster;
    string filename;
    int n;
public:
    OutputPrinter(int n, string filename, vector<vector<int> > cluster) {
        this->n = n;
        this->cluster = cluster;
        
        // remove ".txt" from filename
        if(filename.size()<4){
            cout << filename << "input file name's format is wrong\n";
            exit(0);
        }
        for(int i=0;i<4;i++) filename.pop_back();
        this->filename = filename;
        
        // sort by size decending order
        sort(cluster.begin(), cluster.end(), [&](const vector<int> i, const vector<int> j) {
            return (int)i.size() > (int)j.size();
        });
    }
    void print() {
        for(int i=0;i<n;i++) {
            fout.open(filename+"_cluster_"+to_string(i)+".txt");
            
            for(int j=0;j<cluster[i].size();j++) {
                fout << cluster[i][j] << endl;
            }
            
            fout.close();
        }
    }
};

// int main(int argc, const char * argv[]) {
//     if(argc!=5) {
//         cout << "Please follow this format. clustering.exe [intput] [n] [eps] [minPts]";
//         return 0;
//     }
    
//     string inputFileName(argv[1]);
//     string n(argv[2]);
//     string eps(argv[3]);
//     string minPts(argv[4]);
    
    
//     return 0;
// }