//#include <iostream>
//using namespace std;
//
//template <typename T>
//class Stack :public Vector<T> {
//public:
//	void push(T const& e) { insert(size(), e); }
//	T pop() { return remove(size() - 1); }
//	T& top() { return *this[size() - 1]; }
//};
//
//void convert(Stack<char> & S, _int64 n, int base) {
//	static char digits[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C","D", "E", "F" };
//	while (n > 0) {
//		S.push(digits[n % base]);
//		n /= base;
//	}
//}
//int main() {
//	Stack<char> S;
//	convert(S, n, base);
//	while (!S.empty()) printf("%c", S.pop());
//}
//bool paren(const char expr[], int lo, int hi) {
//	Stack<char> S;
//	for (int i = lo; i < hi; i++) {
//		if (expr[i] == "(") S.push(expr[i]);
//		else if (!S.empty()) S.pop();
//		else return false;
//	}
//	return S.empty();
//}
//
//float evaluate(char* S, char* & RPN) {
//	Stack<float> opnd;
//	Stack<char> optr;
//	optr.push("\0");
//	while (!optr.empty()) {
//		if (isdigit(*S)) readNumber(S, opnd);
//		else switch(orderBetween(optr.pop(), *S){
//		case '<':
//			optr.push(*S); S++; break;
//		case '=':
//			optr.pop(); S++; break;
//		case '>':
//			char op = optr.pop();
//			if ('!' == op) opnd.push(calcu(op, opnd.pop()));
//			else
//			{
//				float popnd2 = opnd.pop(); float popnd1 = opnd.pop();
//				opnd.push(calcu(popnd2, op, popnd1));
//			}
//			break;
//		}
//	}
//	return opnd.pop();
//}
//
//template <typename T>
//class Queue :public List<T> {
//public:
//	void enqueue(T const& e) { insertAsLast(T e); }
//	T dequeue() { return remove(first()); }
//	T& front() { return first()->data; }
//};

#include <iostream>
using namespace std;
int main() {
	cout << !0 << endl;
	return 0;
}