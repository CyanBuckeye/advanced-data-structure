//template class for segment tree
//Example: for a segment tree built on an array of {1,2}, its structure is like:
//                                              {_L: 0, _R: 3, _idx: 0, _max_val: 2, _min_val: 1, _sum_val: 3}
//                                                /                                                      \
//     {_L: 0, _R: 1, _idx: 1, _max_val: 1, _min_val: 1, _sum_val: 1}   {_L: 1, _R: 2,, _idx: 2, _max_val: 2, _min_val: 2, _sum_val: 2}  
//
#include<iostream>
#include<math.h>
#include<vector>
#include<exception>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
using namespace std;


template <typename T> class segmentTree;
//template class for tree node
template <typename T> class _segmentTree_node {
	friend class segmentTree<T>;
	T _max_val, _min_val, _sum_val, _add_val;
	bool _flag;//if the node has not been set value yet, flag is false
public:
	_segmentTree_node();
};

template <typename T> class segmentTree {
public:
	typedef _segmentTree_node<T>* iterator;
	segmentTree(const std::initializer_list<T>&& li);
	segmentTree(const std::vector<T>& vec);
	segmentTree(segmentTree<T>&& tree) noexcept;
	void add(const size_t L, const size_t R, const T& _add_val);
	void add(const size_t L, const size_t R, const T&& _add_val);
	T query_min(const size_t L, const size_t R);
	T query_max(const size_t L, const size_t R);
	T query_sum(const size_t L, const size_t R);
	std::vector<T> query(const size_t L, const size_t R);
	~segmentTree();
private:
	size_t _size, _num;//_size: number of all nodes (O(n*log(n))); _num: number of leaf nodes (O(n))
	_segmentTree_node<T>* root;
	size_t _get_size(const std::initializer_list<T>&& li);
	size_t _get_size(const std::vector<T>& vec);
	void _add_helper(const size_t idx, const size_t L, const size_t R, const size_t curr_L, const size_t curr_R, const T& _add_val);
	void _add_helper(const size_t idx, const size_t L, const size_t R, const size_t curr_L, const size_t curr_R, const T&& _add_val);
	void _query_helper(T* ret_val, bool* flag, const size_t idx, const size_t L, const size_t R, const size_t curr_L, const size_t curr_R, const T carry);
	//iterator _begin_ptr, _end_ptr; //iterator: ToDo
};

template <typename T>
_segmentTree_node<T>::_segmentTree_node() {
	_max_val = T();
	_min_val = T();
	_sum_val = T();
	_add_val = T();
	_flag = false;
}

template<typename T>
size_t segmentTree<T>::_get_size(const std::initializer_list<T>&& li) {
	size_t sz = li.size();
	int order = log2(sz), temp;
	if ((1 << order) == sz) temp = sz;
	else {
		order++;
		temp = (1 << order);
	}
	_num = temp;
	return 2 * temp - 1;
}

template<typename T>
size_t segmentTree<T>::_get_size(const std::vector<T>& vec) {
	size_t sz = vec.size();
	int order = log2(sz), temp;
	if ((1 << order) == sz) temp = sz;
	else {
		order++;
		temp = (1 << order);
	}
	_num = temp;
	return 2 * temp - 1;
}

template<typename T>
void segmentTree<T>::_add_helper(const size_t idx, const size_t L, const size_t R, const size_t curr_L, const size_t curr_R, const T& val)
{
    if(curr_L >= curr_R) return;
	if (L <= curr_L && curr_R <= R) {
		if(root[idx]._flag){
		    root[idx]._max_val = root[idx]._max_val + val;
		    root[idx]._min_val = root[idx]._min_val + val;
		    root[idx]._sum_val = root[idx]._sum_val + (curr_R - curr_L) * val;
		    root[idx]._add_val = root[idx]._add_val + val;
		}
		else{
			root[idx]._flag = true;
			root[idx]._max_val = val;
			root[idx]._min_val = val;
			root[idx]._sum_val = (curr_R - curr_L) * val;
			root[idx]._add_val = val; 
		}
	}
	else {
        if(curr_R - curr_L == 1) return;
        size_t mid = curr_L + (curr_R - curr_L) / 2;
		if (L < mid) {
			_add_helper(2 * idx + 1, L, R, curr_L, mid, val);
		}
		if (R > mid){
			_add_helper(2 * idx + 2, L, R, mid, curr_R, val);
		}
		
		if(root[2 * idx + 1]._flag && root[2 * idx + 2]._flag){
		    if (root[2 * idx + 1]._max_val > root[2 * idx + 2]._max_val)
			{
				if(root[idx]._flag) root[idx]._max_val = root[2 * idx + 1]._max_val + root[idx]._add_val;
				else root[idx]._max_val = root[2 * idx + 1]._max_val;
			}
		    else{
				if(root[idx]._flag) root[idx]._max_val = root[2 * idx + 2]._max_val + root[idx]._add_val;
				else root[idx]._max_val = root[2 * idx + 2]._max_val;
			}

		    if (root[2 * idx + 1]._min_val < root[2 * idx + 2]._min_val)
			 {
				if(root[idx]._flag) root[idx]._min_val = root[2 * idx + 1]._min_val + root[idx]._add_val;
				else root[idx]._min_val = root[2 * idx + 1]._min_val;
			 }
		    else{
				if(root[idx]._flag) root[idx]._min_val = root[2 * idx + 2]._min_val + root[idx]._add_val;
				else root[idx]._min_val = root[2 * idx + 2]._min_val;
			}
 
			if(root[idx]._flag) root[idx]._sum_val = root[2 * idx + 1]._sum_val + root[2 * idx + 2]._sum_val + (curr_R - curr_L) * root[idx]._add_val;//dont forget to add '(curr_R - curr_L) * root[idx]._add_val'
			else root[idx]._sum_val = root[2 * idx + 1]._sum_val + root[2 * idx + 2]._sum_val;
		}
		else{
			if(root[2 * idx + 1]._flag){
				if(root[idx]._flag){
				    root[idx]._max_val = root[2 * idx + 1]._max_val + root[idx]._add_val;
				    root[idx]._min_val = root[2 * idx + 1]._min_val + root[idx]._add_val;
				    root[idx]._sum_val = root[2 * idx + 1]._sum_val + (curr_R - curr_L) * root[idx]._add_val;
				}
				else{
					root[idx]._max_val = root[2 * idx + 1]._max_val;
					root[idx]._min_val = root[2 * idx + 1]._min_val;
					root[idx]._sum_val = root[2 * idx + 1]._sum_val;
				}
			}
			else{
				if(root[2 * idx + 2]._flag){
					if(root[idx]._flag){
					    root[idx]._max_val = root[2 * idx + 2]._max_val + root[idx]._add_val;
					    root[idx]._min_val = root[2 * idx + 2]._min_val + root[idx]._add_val;
						root[idx]._sum_val = root[2 * idx + 2]._sum_val + (curr_R - curr_L) * root[idx]._add_val;
					}
					else{
						root[idx]._max_val = root[2 * idx + 2]._max_val;
					    root[idx]._min_val = root[2 * idx + 2]._min_val;
						root[idx]._sum_val = root[2 * idx + 2]._sum_val;
					}
				}
			}
		}
		root[idx]._flag = true;
	}
}

template<typename T>
void segmentTree<T>::add(const size_t L, const size_t R, const T& val) {
	if (L >= R) throw std::runtime_error("L must be smaller than R");
	_add_helper(0, L, R, 0, _num, val);
}


template<typename T>
void segmentTree<T>::_add_helper(const size_t idx, const size_t L, const size_t R, const size_t curr_L, const size_t curr_R, const T&& val)
{
	if(curr_L >= curr_R) return;
	if (L <= curr_L && curr_R <= R) {
		if(root[idx]._flag){
		    root[idx]._max_val = root[idx]._max_val + val;
		    root[idx]._min_val = root[idx]._min_val + val;
		    root[idx]._sum_val = root[idx]._sum_val + (curr_R - curr_L) * val;
		    root[idx]._add_val = root[idx]._add_val + val;
		}
		else{
			root[idx]._flag = true;
			root[idx]._max_val = val;
			root[idx]._min_val = val;
			root[idx]._sum_val = (curr_R - curr_L) * val;
			root[idx]._add_val = val; 
		}
	}
	else {
        if(curr_R - curr_L == 1) return;
        size_t mid = curr_L + (curr_R - curr_L) / 2;
		if (L < mid) {
			_add_helper(2 * idx + 1, L, R, curr_L, mid, val);
		}
		if (R > mid){
			_add_helper(2 * idx + 2, L, R, mid, curr_R, val);
		}
		
		if(root[2 * idx + 1]._flag && root[2 * idx + 2]._flag){
		    if (root[2 * idx + 1]._max_val > root[2 * idx + 2]._max_val)
			{
				if(root[idx]._flag) root[idx]._max_val = root[2 * idx + 1]._max_val + root[idx]._add_val;
				else root[idx]._max_val = root[2 * idx + 1]._max_val;
			}
		    else{
				if(root[idx]._flag) root[idx]._max_val = root[2 * idx + 2]._max_val + root[idx]._add_val;
				else root[idx]._max_val = root[2 * idx + 2]._max_val;
			}

		    if (root[2 * idx + 1]._min_val < root[2 * idx + 2]._min_val)
			 {
				if(root[idx]._flag) root[idx]._min_val = root[2 * idx + 1]._min_val + root[idx]._add_val;
				else root[idx]._min_val = root[2 * idx + 1]._min_val;
			 }
		    else{
				if(root[idx]._flag) root[idx]._min_val = root[2 * idx + 2]._min_val + root[idx]._add_val;
				else root[idx]._min_val = root[2 * idx + 2]._min_val;
			}
 
			if(root[idx]._flag) root[idx]._sum_val = root[2 * idx + 1]._sum_val + root[2 * idx + 2]._sum_val + (curr_R - curr_L) * root[idx]._add_val;//dont forget to add '(curr_R - curr_L) * root[idx]._add_val'
			else root[idx]._sum_val = root[2 * idx + 1]._sum_val + root[2 * idx + 2]._sum_val;
		}
		else{
			if(root[2 * idx + 1]._flag){
				if(root[idx]._flag){
				    root[idx]._max_val = root[2 * idx + 1]._max_val + root[idx]._add_val;
				    root[idx]._min_val = root[2 * idx + 1]._min_val + root[idx]._add_val;
				    root[idx]._sum_val = root[2 * idx + 1]._sum_val + (curr_R - curr_L) * root[idx]._add_val;
				}
				else{
					root[idx]._max_val = root[2 * idx + 1]._max_val;
					root[idx]._min_val = root[2 * idx + 1]._min_val;
					root[idx]._sum_val = root[2 * idx + 1]._sum_val;
				}
			}
			else{
				if(root[2 * idx + 2]._flag){
					if(root[idx]._flag){
					    root[idx]._max_val = root[2 * idx + 2]._max_val + root[idx]._add_val;
					    root[idx]._min_val = root[2 * idx + 2]._min_val + root[idx]._add_val;
						root[idx]._sum_val = root[2 * idx + 2]._sum_val + (curr_R - curr_L) * root[idx]._add_val;
					}
					else{
						root[idx]._max_val = root[2 * idx + 2]._max_val;
					    root[idx]._min_val = root[2 * idx + 2]._min_val;
						root[idx]._sum_val = root[2 * idx + 2]._sum_val;
					}
				}
			}
		}
		root[idx]._flag = true;
	}
}

template<typename T>
void segmentTree<T>::add(const size_t L, const size_t R, const T&& val) {
	if (L >= R) throw std::runtime_error("L must be smaller than R");
	_add_helper(0, L, R, 0, _num, val);
}

template<typename T>
segmentTree<T>::segmentTree(const std::initializer_list<T>&& li) {
	_size = _get_size(li);
    root = new _segmentTree_node<T>[_size];
    for(size_t i = 0; i < li.size(); i++)
        add(i, i + 1, li[i]);
}

template<typename T>
segmentTree<T>::segmentTree(const std::vector<T>& vec) {
	_size = _get_size(vec);
    root = new _segmentTree_node<T>[_size];
    for(size_t i = 0; i < vec.size(); i++)
        add(i, i + 1, vec[i]);
}

template<typename T>
segmentTree<T>::segmentTree(segmentTree<T>&& tree) noexcept{
	this->root = tree->root;
	this->_size = tree->_size;
	this->_num = tree->_num;
	tree->root = NULL;
}

template<typename T>
segmentTree<T>::~segmentTree() {
	delete[]root;
}

template<typename T>
void segmentTree<T>::_query_helper(T* ptr, bool* find_or_not, const size_t idx, const size_t L, const size_t R, const size_t curr_L, const size_t curr_R, const T carry)
{
    if(curr_L >= curr_R) return;
	if (L <= curr_L && curr_R <= R)
	{
		if (!*find_or_not) {
			ptr[0] = root[idx]._min_val + carry;
			ptr[1] = root[idx]._max_val + carry;
			ptr[2] = root[idx]._sum_val + (curr_R - curr_L) * carry;
			*find_or_not = true;
		}
		else {
			if (root[idx]._min_val + carry < ptr[0]) ptr[0] = root[idx]._min_val + carry;
			if (root[idx]._max_val + carry > ptr[1]) ptr[1] = root[idx]._max_val + carry;
			ptr[2] = ptr[2] + root[idx]._sum_val + (curr_R - curr_L) * carry;
		}
		return;
	}
	else {
        if(curr_R - curr_L == 1) return;
		size_t mid = curr_L + (curr_R - curr_L) / 2;
		if (L < mid) _query_helper(ptr, find_or_not, 2 * idx + 1, L, R, curr_L, mid, carry + root[idx]._add_val);
		if (R > mid) _query_helper(ptr, find_or_not, 2 * idx + 2, L, R, mid, curr_R, carry + root[idx]._add_val);
	}
}

template<typename T>
T segmentTree<T>::query_min(const size_t L, const size_t R)
{
	if (L >= R) throw std::runtime_error("L must be smaller than R");
	T* ptr = new T[3];
	bool flag = false;
	T carry = T();
	_query_helper(ptr, &flag, 0, L, R, 0, _num, carry);
	int ret_val = ptr[0];
	delete[]ptr;
	return ret_val;
}

template<typename T>
T segmentTree<T>::query_max(const size_t L, const size_t R)
{
	if (L >= R) throw std::runtime_error("L must be smaller than R");
	T* ptr = new T[3];
	bool flag = false;
	T carry = T();
	_query_helper(ptr, &flag, 0, L, R, 0, _num, carry);
	int ret_val = ptr[1];
	delete[]ptr;
	return ret_val;
}

template<typename T>
T segmentTree<T>::query_sum(const size_t L, const size_t R)
{
	if (L >= R) throw std::runtime_error("L must be smaller than R");
	T* ptr = new T[3];
	bool flag = false;
	T carry = T();
	_query_helper(ptr, &flag, 0, L, R, 0, _num, carry);
	int ret_val = ptr[2];
	delete[]ptr;
	return ret_val;
}

template<typename T>
std::vector<T> segmentTree<T>::query(const size_t L, const size_t R)
{
	if (L >= R) throw std::runtime_error("L must be smaller than R");
	T* ptr = new T[3];
	bool flag = false;
	T carry = T();
	_query_helper(ptr, &flag, 0, L, R, 0, _num, carry);
	std::vector<T> vec;
	vec.push_back(ptr[0]);
	vec.push_back(ptr[1]);
	vec.push_back(ptr[2]);
	delete[]ptr;
	return vec;
}