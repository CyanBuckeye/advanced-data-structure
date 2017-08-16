#include"../segmentTree.h"
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<climits>
using namespace std;

void brute_force_check_double(vector<double>& vec, int test_round){
    srand((unsigned)time(NULL));
    size_t len = vec.size();
    double cg_val;
    double min_val, max_val, sum_val;
    time_t start = clock();
    size_t L = -1, R = -1;
    for(int i = 0; i < test_round; i++){
        do{
            L = rand() % len;
            R = rand() % len;
        } while(L >= R);
        
    max_val = vec[L];
    min_val = vec[L];
    sum_val = vec[L];
    for (int j = L + 1; j < R; j++)
    {
        if(vec[i] > max_val) max_val = vec[j];
            if(vec[i] < min_val) min_val = vec[j];
            sum_val += vec[j];	
    }
    do{
        L = rand() % len;
        R = rand() % len;
    } while(L >= R);
    cg_val = rand() / double(RAND_MAX);
    for(int j = L + 1; j < R; j++)
        vec[j] = cg_val;
    }
    time_t end = clock();
    cout << "time needed by brute force is " << double(end - start) / CLOCKS_PER_SEC << endl;       
}

void check_segTree_double(vector<double>& vec, int test_round){
    size_t len = vec.size();
    time_t start = clock();
    segmentTree<double>* tree = new segmentTree<double>(vec);
    srand((unsigned)time(NULL));
    size_t L = -1, R = -1;
    double cg_val;
    for(int i = 0; i < test_round; i++){
        do{
            L = rand() % len;
            R = rand() % len;
        } while(L >= R);
        int val = tree->query_min(L, R);
        cg_val = rand() / double(RAND_MAX);
        do{
            L = rand() % len;
            R = rand() % len;
        } while(L >= R);
        tree->set(L, R, cg_val);
    }
    time_t end = clock();
    cout << "time needed by segment tree is " << double(end - start) / CLOCKS_PER_SEC << endl;
}

int main() {
    int li_len = 1000000;
    int test_round = 1000;

    ///Check T == DOUBLE
    srand((unsigned)time(NULL));
    vector<double> d_vec;
    double d_rand_val;
    for(int i = 0; i < li_len; i++){
        d_rand_val = rand() / double(RAND_MAX);
        d_vec.push_back(d_rand_val);
    }
    
    check_segTree_double(d_vec, test_round);
    brute_force_check_double(d_vec, test_round);
	return 0;
}
