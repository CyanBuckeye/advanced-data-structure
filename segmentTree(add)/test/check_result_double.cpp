#include"../segmentTree.h"
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<climits>
#include<fstream>
using namespace std;

//check outputs of segment tree on DOUBLE
void check_result_double(vector<double>& vec, int test_round, ostream& brute_strm, ostream& segtree_strm){
    srand((unsigned)time(NULL));
    size_t len = vec.size();
    double cg_val;
    double min_val, max_val, sum_val;
    time_t start = clock();
    size_t L = -1, R = -1;
    segmentTree<double>* tree = new segmentTree<double>(vec);
    for(int i = 0; i < test_round; i++){
        do{
            L = rand() % len;
            R = rand() % len;
        } while(L >= R);// randomly pick L, R
        
        max_val = vec[L];
        min_val = vec[L];
        sum_val = vec[L];
        for (int j = L + 1; j < R; j++)//get minimum, maximum and sum among [L, R) by brute force method
        {
            if(vec[j] > max_val) max_val = vec[j];
            if(vec[j] < min_val) min_val = vec[j];
            sum_val += vec[j];	
        }
        brute_strm << max_val << " " << min_val << " " << sum_val << endl; 
        auto temp_ans = tree->query(L, R);// query with segment tree
        segtree_strm << temp_ans[1] << " " << temp_ans[0] << " " << temp_ans[2] << endl;
        do{
            L = rand() % len;
            R = rand() % len;
        } while(L >= R);// then randomly get L and R again
        cg_val = rand() / double(RAND_MAX);

        for(int j = L; j < R; j++) // brute force to update value: set vec[L] ... vec[R - 1] to be cg_val
            vec[j] += cg_val;

        tree->add(L, R, cg_val); // set with segment tree
    }
}

int main(int argc, char* argv[]) {
    if(argc < 3) throw runtime_error("too few arguments");
    ofstream brute_f(argv[1]);
    ofstream  seg_f(argv[2]);
    int li_len = 1000000; // length of array
    int test_round = 1000;
	
    srand((unsigned)time(NULL));// use current time as seed of random generator
    vector<double> d_vec;
    double d_rand_val;
    for(int i = 0; i < li_len; i++){
        d_rand_val = rand() / double(RAND_MAX); // get random double number
        d_vec.push_back(d_rand_val);
    }
    check_result_double(d_vec, test_round, brute_f, seg_f);
    return 0;
}
