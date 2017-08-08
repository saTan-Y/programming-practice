#include <iostream>
#include "My_vector.h"

using namespace std;

template <typename T>
void Vector<T>::copyfrom(T const* A, Rank lo, Rank hi) {
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while (lo < hi)
		_elem[_size++] = A[lo++];
}
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& v) {
	if (_elem) delete[] _elem;
	copyfrom(v._elem, 0, v.size()));
	return *this;
}
template <typename T>
void Vector::expand() {
	if (_size < _capacity) return;
	_capacity = max(_size, _capacity);
	T* oldelem = _elem;
	_elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldelem[i];
	delete[] oldelem;
}
template <typename T>
Rank Vector<T>::insert(Rank r, T const& e) {
	expand();
	for (int i = _size; i > r; i--)
		_elem[i] = _elem[i - 1];
	_elem[r] = e; 
	_size++;
	return r;
}
template <typename T> 
int Vector<T>::remove(Rank lo, Rank high) {
	if (lo == hi) return 0;
	while (hi < _size)
		_elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();
	return	hi - lo;
}
template <typename T>
int Vector<T>::remove(Rank r) {
	T e _elem[r];
	remove(r, r + 1);
	return e;
}
template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) {
	while ((lo < hi--) && (e != _elem(hi)));
	return hi;
}
template <typename T>
int Vector<T>::deduplicate() {
	int oldsize = _size;
	int i = 1;
	while (i < _size)
		(find(_elem[i], 0, i) < 0) ? i++ : remove(i);
	return oldsize - _size;
}
template <typename T>
void Vector<T>::traverse(void(*visit)(T&)) {
	for (i = 0; i < _size; i++)
		visit(_elem[i]);
}
template <typename T>
int Vector<T>::disordered() {
	int n = 0;
	for (i = 1; i < _size; i++)
		n += (_elem[i - 1] > _elem[i]);
	return n;
}
template <typename T>
int Vector<T>::uniquify(){
	Rank i = 0, j = 0;
	while (++j < _size) {
		if (_elem[i] != _elem[j])
			_elem[++i] = _elem[j];
	}
	_size = ++i;
	return j - i;
}
template <typename T>
static Rank Vector<T>::binSearch(T const& e, Rank lo, Rank hi) {
	while (lo < hi) {
		Rank mi = (lo + hi) >> 1;
		if (e < _elem[mi])
			hi = mi;
		else if (_elem[mi] < e)
				lo = mi + 1;
		else
			return mi;
	}
	return -1;
}

void bubblesort(int A[], int n) {
	for (bool sorted = false; sorted = !sorted; n--) {
		for (int i = 1; i < n; i++) {
			if (A[i - 1] < A[i]) {
				swap(A[i - 1], A[i]);
				sorted = false;
			}
		}
	}
}

template <typename T> 
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
	while (lo<(hi=bubble(lo, hi--)));
}
template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {
	Rank last = lo;
	while (++lo < hi) {
		if (_elem[lo - 1] > _elem[lo]) {
			swap(_elem[lo - 1], _elem[lo]);
			last = lo;
		}
	}
	return last;
}

template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
	if (hi - lo < 2)
		return;
	int mi = (lo + hi) >> 1;
	mergeSort(lo, mi);
	mergeSort(mi, hi);
	merge(lo, mi, hi);
}

template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
	T* A = _elem + lo;
	lb = mi - hi;
	T* B = new T[lb];
	lc = hi - mi;
	T* C = _elem + mi;
	for (Rank i = 0, j = 0, k = 0; j < lb;) {
		if ((k < lc) &&  (C[k] < B[j])
			A[i++] = C[k++];
		if ((lc <= k) || (B[j] <= C[k])
			A[i++] = B[j++];
	}
	delete[] B;
}