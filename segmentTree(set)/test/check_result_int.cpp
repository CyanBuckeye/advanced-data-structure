#include"../segmentTree.h"
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<climits>
#include<fstream>
using namespace std;

//check outputs of segment tree on INT
void check_result_int(vector<int>& vec, int test_round, ostream& brute_strm, ostream& segtree_strm){
    srand((unsigned)time(NULL));
    size_t len = vec.size();
    int cg_val;
    int min_val, max_val, sum_val;
    time_t start = clock();
    size_t L = -1, R = -1;
    segmentTree<int>* tree = new segmentTree<int>(vec);
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
            if(vec[j] > max_val) max_val = vec[j];
            if(vec[j] < min_val) min_val = vec[j];
            sum_val += vec[j];	
        }
        brute_strm << max_val << " " << min_val << " " << sum_val << endl;
        auto temp_ans = tree->query(L, R);
        segtree_strm << temp_ans[1] << " " << temp_ans[0] << " " << temp_ans[2] << endl;
        do{
            L = rand() % len;
            R = rand() % len;
        } while(L >= R);
        cg_val = rand();

        for(int j = L; j < R; j++)
            vec[j] = cg_val;

        tree->set(L, R, cg_val);
    }
}

int main(int argc, char* argv[]) {
    if(argc < 3) throw runtime_error("too few arguments");
    ofstream brute_f(argv[1]);
    ofstream  seg_f(argv[2]);
    int li_len = 1000000;
    int test_round = 1000;

	srand((unsigned)time(NULL));
	vector<int> vec;
	int rand_val;
	for (int i = 0; i < li_len; i++) {
		rand_val = rand();
		vec.push_back(rand_val);
	}
    check_result_int(vec, test_round, brute_f, seg_f);
    return 0;
}
