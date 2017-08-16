#include"segmentTree.h"
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<climits>
using namespace std;

struct test_element{
    int min_val, max_val, sum_val;
};

void brute_force_check(vector<int>& vec, int test_round) {
        srand((unsigned)time(NULL));
        size_t len = vec.size();
        int cg_val;
        test_element ret_val;
        time_t start = clock();
        size_t L = -1, R = -1;
        for(int i = 0; i < test_round; i++){
            do{
                L = rand() % len;
                R = rand() % len;
            } while(L >= R);
            
	    ret_val.max_val = vec[L];
	    ret_val.min_val = vec[L];
	    ret_val.sum_val = vec[L];
	    for (int j = L + 1; j < R; j++)
	    {
	        if(vec[i] > ret_val.max_val) ret_val.max_val = vec[j];
                if(vec[i] < ret_val.min_val) ret_val.min_val = vec[j];
                ret_val.sum_val += vec[j];	
	    }
            do{
                L = rand() % len;
                R = rand() % len;
            } while(L >= R);
            cg_val = rand();
            for(int j = L + 1; j < R; j++)
                vec[j] = cg_val;
        }
        time_t end = clock();
        cout << "time needed by brute force is " << double(end - start) / CLOCKS_PER_SEC << endl;       
}

void check_segTree_int(vector<int>& vec, int test_round){
    size_t len = vec.size();
    time_t start = clock();
    segmentTree<int>* tree = new segmentTree<int>(vec);
    srand((unsigned)time(NULL));
    size_t L = -1, R = -1;
    int cg_val;
    for(int i = 0; i < test_round; i++){
        do{
            L = rand() % len;
            R = rand() % len;
        } while(L >= R);
        int val = tree->query_min(L, R);
         cg_val = rand();
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
	srand((unsigned)time(NULL));
	int li_len = 1000000;
        int test_round = 1000;
	vector<int> vec;
	int rand_val;
	for (int i = 0; i < li_len; i++) {
		rand_val = rand();
		vec.push_back(rand_val);
	}
        
        check_segTree_int(vec, test_round); 
        brute_force_check(vec, test_round);
	///////////Check T == int: it works
	return 0;
}
