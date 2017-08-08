#ifndef VECTOR_MY_VECTOR_
#define VECTOR_MY_VECTOR_
typedef int Rank;
#define DEFAULT_CAPACITY 3

template <typename T> class Vector {
protected:
	Rank _size; int _capacity; T* _elem;
	void copyfrom(T const* A, Rank lo, Rank hi);
	void expand();
	void shrink();
	bool bubble(Rank lo, Rank hi);
	void bubbleSort(Rank lo, Rank hi);
	Rank max(Rank lo, Rank hi);
	void selectionSort(Rank lo, Rank hi);
	void merge(Rank lo, Rank mi, Rank hi);
	Rank partition(Rank lo, Rank hi);
	void quickSort(Rank lo, Rank, hi);
	void heapSort(Rank lo, Rank hi);
public:
	Vector(int c = DEFAULT_CAPACIT, int s = 0, T v = 0)//容量c规模s所有元素初始为v
	{
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);
	}
	Vector(T* const A, Rank n) {
		copyfrom(A, 0, n);
	}
	Vector(T* const A, Rank lo, Rank hi) {
		copyfrom(A, lo, hi);
	}
	Vector(Vector<T> const& v) {
		copyfrom(V._elem, 0, V._size);
	}
	Vector(Vector<T> const& v, Rank lo, Rank hi) {
		copyfrom(V._elem, lo, hi);
	}
	~Vector() {
		delete[] _elem;
	}
	Rank size() const {
		return _size;
	}
	bool empty() const {
		return !_size;
	}
	int disordered() const;
	Rank find(T const& e) {
		return find(e, 0, _size);
	}
	Rank find(T const& e, Rank lo, Rank hi) const;
	Rank find(T const& e) const;
	Rank search(T const& e) const {
		return (0 > _size) ? -1 : search(e, 0, _size);
	}
	Rank search(T const& e) const;
	T& operator[](Rank r) const;
	Vector<T>& operator=(Vector<T> const&);
	T remove(Rank r);
	int remove(Rank lo, Rank hi);
	Rank insert(Rank r, T const& e);
	Rank insert(T const& e) {
		return insert(_size, e);
	}
	void sort(Rank lo, Rank hi);
	void sort() {
		sort(0, _size);
	}
	void unsort(Rank lo, Rank hi);
	void unsort() {
		unsort(0, _size);
	}
	int deduplicate();
	int uniquify();
	void traverse(void(*)(T&));
	template <typename VST> void traverse(VST&)
};
#endif
