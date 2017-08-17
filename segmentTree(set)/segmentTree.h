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

template <typename T> class segmentTree;
//template class for tree node
template <typename T> class _segmentTree_node {
	friend class segmentTree<T>;
	size_t _L, _R, _Idx;
	T _max_val, _min_val, _sum_val, _set_val;
	bool _is_set;
	bool _is_default;
public:
	_segmentTree_node();
};

template <typename T> class segmentTree {
public:
	typedef _segmentTree_node<T>* iterator;
	segmentTree(const std::initializer_list<T>&& li);
	segmentTree(const std::vector<T>& vec);
	segmentTree(segmentTree<T>&& tree) noexcept;
	void set(const size_t L, const size_t R, const T& _set_val);
	void set(const size_t L, const size_t R, const T&& _set_val);
	T query_min(const size_t L, const size_t R);
	T query_max(const size_t L, const size_t R);
	T query_sum(const size_t L, const size_t R);
	std::vector<T> query(const size_t L, const size_t R);
	~segmentTree();
private:
	size_t _size;
	_segmentTree_node<T>* root;
	size_t _get_size(const std::initializer_list<T>&& li);
	size_t _get_size(const std::vector<T>& vec);
	void _set_default_val(const size_t idx, const size_t L, const size_t R);
	void _set_helper(const size_t idx, const size_t L, const size_t R, const T& _set_val);
	void _set_helper(const size_t idx, const size_t L, const size_t R, const T&& set_val);
	void _query_helper(T* ret_val, bool* flag, const size_t idx, const size_t L, const size_t R);
	void _assign_val(const size_t idx, const size_t L, const size_t R, const T& val);
	void _assign_val(const size_t idx, const size_t L, const size_t R, const T&& val);
	//iterator _begin_ptr, _end_ptr;
};

template <typename T>
_segmentTree_node<T>::_segmentTree_node() {
	_is_set = false;
	_is_default = true;
}

template <typename T>
void segmentTree<T>::_assign_val(const size_t idx, const size_t L, const size_t R, const T& val)
{
	size_t curr_L = root[idx]._L, curr_R = root[idx]._R;
	if (L <= curr_L && curr_R <= R) {
		root[idx]._max_val = val;
		root[idx]._min_val = val;
		root[idx]._sum_val = (curr_R - curr_L) * val;
		root[idx]._is_default = false;
		root[idx]._set_val = val;
	}
	else {
		size_t mid = curr_L + (curr_R - curr_L) / 2;
		if (L < mid) _assign_val(2 * idx + 1, L, R, val);
		if (R > mid) _assign_val(2 * idx + 2, L, R, val);

		if (!root[2 * idx + 1]._is_default && !root[2 * idx + 2]._is_default) {
			if (root[2 * idx + 1]._max_val > root[2 * idx + 2]._max_val)
				root[idx]._max_val = root[2 * idx + 1]._max_val;
			else
				root[idx]._max_val = root[2 * idx + 2]._max_val;

			if (root[2 * idx + 1]._min_val < root[2 * idx + 2]._min_val)
				root[idx]._min_val = root[2 * idx + 1]._min_val;
			else
				root[idx]._min_val = root[2 * idx + 2]._min_val;

			root[idx]._sum_val = root[2 * idx + 1]._sum_val + root[2 * idx + 2]._sum_val;
		}
		else {
			if (!root[2 * idx + 1]._is_default) {
				root[idx]._max_val = root[2 * idx + 1]._max_val;
				root[idx]._min_val = root[2 * idx + 1]._min_val;
				root[idx]._sum_val = root[2 * idx + 1]._sum_val;
			}
			else {
				if (!root[2 * idx + 2]._is_default) {
					root[idx]._max_val = root[2 * idx + 2]._max_val;
					root[idx]._min_val = root[2 * idx + 2]._min_val;
					root[idx]._sum_val = root[2 * idx + 2]._sum_val;
				}
			}
		}
		root[idx]._is_default = false;
	}
}

template <typename T>
void segmentTree<T>::_assign_val(const size_t idx, const size_t L, const size_t R, const T&& val) {
	size_t curr_L = root[idx]._L, curr_R = root[idx]._R;
	if (L <= curr_L && curr_R <= R) {
		root[idx]._max_val = val;
		root[idx]._min_val = val;
		root[idx]._sum_val = (curr_R - curr_L) * val;
		root[idx]._is_default = false;
		root[idx]._set_val = val;
	}
	else {
		size_t mid = curr_L + (curr_R - curr_L) / 2;
		if (L < mid) _assign_val(2 * idx + 1, L, R, val);
		if (R > mid) _assign_val(2 * idx + 2, L, R, val);

		if (!root[2 * idx + 1]._is_default && !root[2 * idx + 2]._is_default) {
			if (root[2 * idx + 1]._max_val > root[2 * idx + 2]._max_val)
				root[idx]._max_val = root[2 * idx + 1]._max_val;
			else
				root[idx]._max_val = root[2 * idx + 2]._max_val;

			if (root[2 * idx + 1]._min_val < root[2 * idx + 2]._min_val)
				root[idx]._min_val = root[2 * idx + 1]._min_val;
			else
				root[idx]._min_val = root[2 * idx + 2]._min_val;

			root[idx]._sum_val = root[2 * idx + 1]._sum_val + root[2 * idx + 2]._sum_val;
		}
		else {
			if (!root[2 * idx + 1]._is_default) {
				root[idx]._max_val = root[2 * idx + 1]._max_val;
				root[idx]._min_val = root[2 * idx + 1]._min_val;
				root[idx]._sum_val = root[2 * idx + 1]._sum_val;
			}
			else {
				if (!root[2 * idx + 2]._is_default) {
					root[idx]._max_val = root[2 * idx + 2]._max_val;
					root[idx]._min_val = root[2 * idx + 2]._min_val;
					root[idx]._sum_val = root[2 * idx + 2]._sum_val;
				}
			}
		}
		root[idx]._is_default = false;
	}
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
	return 2 * temp - 1;
}

template<typename T>
void segmentTree<T>::_set_helper(const size_t idx, const size_t L, const size_t R, const T& val)
{
	size_t curr_L = root[idx]._L, curr_R = root[idx]._R;
	if (L <= curr_L && curr_R <= R) {
		root[idx]._max_val = val;
		root[idx]._min_val = val;
		root[idx]._sum_val =  (curr_R - curr_L) * val;
		root[idx]._is_set = true;
		root[idx]._set_val = val;
	}
	else {
		if (root[idx]._is_set) {
			_set_helper(2 * idx + 1, curr_L, curr_R, root[idx]._set_val);
			_set_helper(2 * idx + 2, curr_L, curr_R, root[idx]._set_val);
			root[idx]._is_set = false;
		}
		size_t mid = curr_L + (curr_R - curr_L) / 2;
		if (L < mid) _set_helper(2 * idx + 1, L, R, val);
		if (R > mid) _set_helper(2 * idx + 2, L, R, val);

		if (root[2 * idx + 1]._max_val > root[2 * idx + 2]._max_val)
			root[idx]._max_val = root[2 * idx + 1]._max_val;
		else
			root[idx]._max_val = root[2 * idx + 2]._max_val;

		if (root[2 * idx + 1]._min_val < root[2 * idx + 2]._min_val)
			root[idx]._min_val = root[2 * idx + 1]._min_val;
		else
			root[idx]._min_val = root[2 * idx + 2]._min_val;

		root[idx]._sum_val = root[2 * idx + 1]._sum_val + root[2 * idx + 2]._sum_val;
	}
}

template<typename T>
void segmentTree<T>::set(const size_t L, const size_t R, const T& val) {
	if (L >= R) throw std::runtime_error("L must be smaller than R");
	_set_helper(0, L, R, val);
}


template<typename T>
void segmentTree<T>::_set_helper(const size_t idx, const size_t L, const size_t R, const T&& val)
{
	size_t curr_L = root[idx]._L, curr_R = root[idx]._R;
	if (L <= curr_L && curr_R <= R) {
		root[idx]._max_val = val;
		root[idx]._min_val = val;
		root[idx]._sum_val = (curr_R - curr_L) * val;
		root[idx]._is_set = true;
		root[idx]._set_val = val;
	}
	else {
		if (root[idx]._is_set) {
			_set_helper(2 * idx + 1, curr_L, curr_R, root[idx]._set_val);
			_set_helper(2 * idx + 2, curr_L, curr_R, root[idx]._set_val);
			root[idx]._is_set = false;
		}
		size_t mid = curr_L + (curr_R - curr_L) / 2;
		if (L < mid) _set_helper(2 * idx + 1, L, R, val);
		if (R > mid) _set_helper(2 * idx + 2, L, R, val);

		if (root[2 * idx + 1]._)
			if (root[2 * idx + 1]._max_val > root[2 * idx + 2]._max_val)
				root[idx]._max_val = root[2 * idx + 1]._max_val;
			else
				root[idx]._max_val = root[2 * idx + 2]._max_val;

		if (root[2 * idx + 1]._min_val < root[2 * idx + 2]._min_val)
			root[idx]._min_val = root[2 * idx + 1]._min_val;
		else
			root[idx]._min_val = root[2 * idx + 2]._min_val;

		root[idx]._sum_val = root[2 * idx + 1]._sum_val + root[2 * idx + 2]._sum_val;
	}
}

template<typename T>
void segmentTree<T>::set(const size_t L, const size_t R, const T&& val) {
	if (L >= R) throw std::runtime_error("L must be smaller than R");
	_set_helper(0, L, R, val);
}

template<typename T>
void segmentTree<T>::_set_default_val(const size_t idx, const size_t L, const size_t R) {
	if (L >= R) return;
	root[idx]._L = L; root[idx]._R = R; root[idx]._Idx = idx;
	if (R - L == 1) return;
	_set_default_val(2 * idx + 1, L, L + (R - L) / 2);
	_set_default_val(2 * idx + 2, L + (R - L) / 2, R);
	return;
}

template<typename T>
segmentTree<T>::segmentTree(const std::initializer_list<T>&& li) {
	_size = _get_size(li);
	root = new _segmentTree_node<T>[_size];
	_set_default_val(0, 0, li.size());
	for (auto iter = li.begin(); iter != li.end(); iter++)
		_assign_val(0, iter - li.begin(), iter - li.begin() + 1, *iter);
}

template<typename T>
segmentTree<T>::segmentTree(const std::vector<T>& vec) {
	_size = _get_size(vec);
	root = new _segmentTree_node<T>[_size];
	_set_default_val(0, 0, vec.size());
	for (auto iter = vec.begin(); iter != vec.end(); iter++)
		_assign_val(0, iter - vec.begin(), iter - vec.begin() + 1, *iter);
}

template<typename T>
segmentTree<T>::segmentTree(segmentTree<T>&& tree) noexcept{
	this->root = tree->root;
	this->_size = tree->_size;
	tree->root = NULL;
}

template<typename T>
segmentTree<T>::~segmentTree() {
	delete[]root;
}

template<typename T>
void segmentTree<T>::_query_helper(T* ptr, bool* find_or_not, const size_t idx, const size_t L, const size_t R)
{
	size_t curr_L = root[idx]._L, curr_R = root[idx]._R;
	if (L <= curr_L && curr_R <= R)
	{
		if (!*find_or_not) {
			ptr[0] = root[idx]._min_val;
			ptr[1] = root[idx]._max_val;
			ptr[2] = root[idx]._sum_val;
			*find_or_not = true;
		}
		else {
			if (root[idx]._min_val < ptr[0]) ptr[0] = root[idx]._min_val;
			if (root[idx]._max_val > ptr[1]) ptr[1] = root[idx]._max_val;
			ptr[2] = ptr[2] + root[idx]._sum_val;
		}
		return;
	}
	else {
		if (root[idx]._is_set) {
			_set_helper(2 * idx + 1, curr_L, curr_R, root[idx]._set_val);
			_set_helper(2 * idx + 2, curr_L, curr_R, root[idx]._set_val);
			root[idx]._is_set = false;
		}
		size_t mid = curr_L + (curr_R - curr_L) / 2;
		if (L < mid) _query_helper(ptr, find_or_not, 2 * idx + 1, L, R);
		if (R > mid) _query_helper(ptr, find_or_not, 2 * idx + 2, L, R);
	}
}

template<typename T>
T segmentTree<T>::query_min(const size_t L, const size_t R)
{
	if (L >= R) throw std::runtime_error("L must be smaller than R");
	T* ptr = new T[3];
	bool flag = false;
	_query_helper(ptr, &flag, 0, L, R);
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
	_query_helper(ptr, &flag, 0, L, R);
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
	_query_helper(ptr, &flag, 0, L, R);
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
	_query_helper(ptr, &flag, 0, L, R);
	std::vector<T> vec;
	vec.push_back(ptr[0]);
	vec.push_back(ptr[1]);
	vec.push_back(ptr[2]);
	delete[]ptr;
	return vec;
}
