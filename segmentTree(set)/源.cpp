#include"segmentTree.h"
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<climits>
using namespace std;

struct element {
	int min_val, max_val, sum_val;
};

element brute_force_check(vector<int>& vec, int L, int R) {
	element ret_val;
	ret_val.max_val = INT_MIN;
	ret_val.min_val = INT_MAX;
	ret_val.sum_val = 0;
	for (int i = L; i < R; i++)
	{
		ret_val.max_val = max(ret_val.max_val, vec[i]);
		ret_val.min_val = min(ret_val.min_val, vec[i]);
		ret_val.sum_val += vec[i];
	}
	return ret_val;
}


int main() {
	/*
	vector<int> vec = { 1,2,3,4,5,6,7 };
	segmentTree<int>* tree = new segmentTree<int>(vec);
	int max_val = tree->query_max(0, 7);
	tree->set(2, 5, -2);
	int min_val = tree->query_min(1, 6);
	tree->set(1, 4, 9);
	max_val = tree->query_max(3, 9);
	*/
	
	srand((unsigned)time(NULL));
	int li_len = 1000000;
	vector<int> vec;
	int rand_val;
	for (int i = 0; i < li_len; i++) {
		rand_val = rand();
		vec.push_back(rand_val);
	}
	
	time_t start = clock();
	segmentTree<int>* tree = new segmentTree<int>(vec);
	int min_val, max_val, sum_val, cg_val;
	int round = 1000;
	for (int i = 0; i < round; i++) {
		int L = -1, R = -1;
		do{
			L = rand() % li_len;
			R = rand() % li_len;
		} while (L >= R);
		cg_val = rand();
		min_val = tree->query_min(L, R);
		//max_val = tree->query_max(L, R);
		//sum_val = tree->query_sum(L, R);
		//auto ans = brute_force_check(vec, L, R);
		//cout << "segment tree min_val: " << min_val << " max_val: " << max_val << " sum_val: " << sum_val << endl;
		//cout << "brute force min_val: " << ans.min_val << " max_val: " << ans.max_val << " sum_val: " << ans.sum_val << endl;
		do {
			L = rand() % li_len;
			R = rand() % li_len;
		} while (L >= R);
		tree->set(L, R, cg_val);
		//for (int i = L; i < R; i++)
		//	vec[i] = cg_val;
	} 
	time_t end = clock();
	cout << double(end - start) / CLOCKS_PER_SEC << endl;
	///////////Check T == int: it works
	return 0;
}