#include <iostream>
#include <time.h>
using namespace std;
class Array {
	int N;
	int* array;
private:
	void QuicksSort(int left, int right) {
		int i = left, j = right - 1;
		int m = array[i + (j - i) / 2]; // використовувати саме так
		while (i <= j) {
			while (array[i] < m)i++;
			while (array[j] > m)j--;
			if (i <= j) {
				swap(array[i], array[j]);
				i++;
				j--;
			}
		}
		if (left < j) QuicksSort(left, j + 1);
		if (i < right) QuicksSort(i, right);
	}
public:
	Array();
	explicit Array(int);
	Array(const Array& Ar);
	~Array();
	int Size() const;
	const int* Data() const;
	int* Data();
	void Clear();
	void Print();
	void SetRnd(int min, int max);
	void Input();
	Array& operator = (const Array& Ar);//this = Ar
	Array operator + (const Array& RAr) const;//this + RAr
	Array operator + (int el) const; //this + el
	//Array operator+(int el); //el   + this error
	friend  Array operator + (int el, const Array& Rar);
	//18.06.2020
	Array operator - ();
	Array operator + ();
	Array& operator ++ ();//постфіксний інкремент
	Array operator ++ (int);//префіксний інкремент
	//оператори порівняння
	bool operator==(const Array& P); // двох обєктів
	bool operator!=(const Array& P);
	bool operator<(const Array& P);
	int operator[](int i) const;
	int& operator[](int i);
	//19.06.2020
	friend ostream& operator<< (ostream& out, const Array& A);
	friend istream& operator>> (istream& in, Array& A);
	Array(Array&& A); // може попасти лише тимчасовий обєкт
	Array& operator = (Array&& A);
	void QuicksSort() { QuicksSort(0, N); }
};
Array::Array() {
	N = 0;
	array = nullptr;
}
//Array::Array(int n) :N(n), array(new int[n] {0})
Array::Array(int n) {
	N = n;
	if (N > 0)
		array = new int[n] {0};
	else
		array = nullptr;
}
//Array::Array(const Array& Ar)
//{
//    N = Ar.N;
//    array = new int[Ar.N];
//    for (size_t i = 0; i < N; i++)
//        array[i] = Ar.array[i];
//}
Array::Array(const Array& Ar) :Array(Ar.N) {
	//copy(Ar.array, Ar.array + N, array);    
	memcpy(array, Ar.array, N * sizeof(*array));
}
Array& Array::operator=(const Array& Ar) {
	cout << "I was" << endl;
	if (&Ar != this) {
		Clear();
		N = Ar.N;
		if (N) {
			array = new int[Ar.N];
			memcpy(array, Ar.array, N * sizeof(*array));
		}
		else
			array = nullptr;
	}
	return *this;
}
Array Array::operator+(const Array& RAr) const {
	Array nar(N + RAr.N);
	memcpy(nar.array, array, N * sizeof(*array));
	memcpy(nar.array + N, RAr.array, RAr.N * sizeof(*(RAr.array)));
	return nar;
}
Array Array::operator+(int el) const {
	Array nar(N + 1);
	memcpy(nar.array, array, N * sizeof(*array));
	nar.array[N] = el;
	return nar;
}
// 18.06.2020
Array Array::operator - () {
	Array temp(*this); // this - переданий сюди обєкт
	for (size_t i = 0; i < N; i++) {
		temp.array[i] *= -1;
	}
	return temp;
}
Array Array::operator + () {
	return *this;
}
//Array operator+(int el, const Array& Rar) { // int + Array
//    Array nar(Rar.Size() + 1);
//    //nar.Data()[0] = el;
//    *nar.Data() = el;
//    memcpy(nar.Data()+1, Rar.Data(), Rar.Size() * sizeof(*Rar.Data()));
//    return nar;
//    //return Rar + el;
//}
Array operator + (int el, const Array& Rar) { // int + Array friend
	Array nar(Rar.N + 1);
	nar.array[0] = el;
	memcpy(nar.array + 1, Rar.array, Rar.N * sizeof(*Rar.array));
	return nar;
}
Array& Array::operator++() { //постфіксний інкремент
	/*
	int a = 10;
	int b ;
	b=a++; // a=11, b=10
	*/
	for (size_t i = 0; i < N; ++i) {
		++array[i];
	}
	return *this;
}
Array Array::operator++(int) {  //префіксний інкремент
	Array temp(*this); // this - переданий сюди обєкт
	++(*this);
	/*for (size_t i = 0; i < N; ++i) {
		temp.array[i] = array[i] + 1;
	}*/
	return temp;
}
bool Array::operator==(const Array& P) {
	if (N != P.N) return false;
	/*for (size_t i = 0; i < N; i++) {
		if (array[i] != P.array[i])
			return false;
		return true;
	}*/
	return !memcmp(array, P.array, N * sizeof(*array)); // "memcmp" перевіряє память побітово на рівність
}
bool Array::operator!=(const Array& P) {
	return !(*this == P);
}
bool Array::operator<(const Array& P) { // решта значкыв аналогычно
	/*
	3 2 1
	3 5 0
	*/
	if (N < P.N)return true;
	if (N == P.N)
		return memcpy(array, P.array, N * sizeof(*array)) < 0 ? true : false;
	return false;
}
int Array::operator[](int i) const {
	if (i >= 0 && i < N)
		return array[i];
	exit(1);
}
int& Array::operator[](int i) {
	if (i >= 0 && i < N)
		return array[i];
	exit(1);
}
Array::~Array() {
	Clear();
	cout << "Destroy obj\n" << endl;
}
int Array::Size() const {
	return N;
}
int* Array::Data() {
	return array;
}
const int* Array::Data() const {
	return array;
}
void Array::Clear() {
	N = 0;
	delete[] array;
	array = nullptr;
}
void Array::Print() {
	for (int i = 0; i < N; i++)
		cout << array[i] << "\t";
	cout << endl;
}
void Array::SetRnd(int min, int max) {
	if (min > max)swap(min, max);
	for (int i = 0; i < N; i++)
		array[i] = min + rand() % (max - min + 1);
}
void Array::Input() {
	for (int i = 0; i < N; i++) {
		cout << "array[" << i << "] = ";
		cin >> array[i];
	}
}
//19.06.2020
ostream& operator<< (ostream& out, const Array& A) {
	for (size_t i = 0; i < A.N; ++i) {
		out << A[i] << '\t';
		out << endl;
	}
	return out;
}
istream& operator>> (istream& in, Array& A) {
	A.Input();
	return in;
}
Array foo() {
	Array A(10000);
	++A;
	return	A;
}
Array::Array(Array&& A) {
	N = A.N;
	array = A.array;
	A.array = nullptr;
	cout << "Move Arr\n";
}
Array& Array::operator=(Array&& A) {
	Clear();
	N = A.N;
	array = A.array;
	A.array = nullptr;
	cout << "Move =\n";
	return *this;
}

int main() {
	////setlocale(LC_ALL, ""); //працює тільки з потоком виведення
	srand(time(0));
	//int f = 10, k = f;
	//Array mas1(3);
	////mas1.Print();
	//mas1.SetRnd(-5, 5);
	//cout << "-------------mas1-------------------\n";
	//mas1.Print();
	//cout << "-------------mas2-------------------\n";
	////mas.Input();
	Array mas2(100);
	////mas1.Print();
	mas2.SetRnd(-500, 500);
	//mas2.Print();
	//cout << "--------------mas3------------------\n";
	//Array mas3;
	//mas3 = mas1 + mas2;
	////mas3 = mas3 + mas3;
	//mas3.Print();
	//cout << "--------------mas3------------------\n";
	//mas3 = mas1 + 30 + 40 + 50 + 60;
	//mas3.Print();
	//cout << "--------------mas3------------------\n";
	//mas3 = 30 + mas1;
	//mas3.Print();
	//cout << "************************18.06.2020***************************" << endl;
	//mas3 = -mas1;
	//mas3.Print();
	//mas1.Print();
	//cout << "*****************************+a*****************************" << endl;
	//mas3 = +mas1;
	//mas3.Print();
	//mas1.Print();
	//cout << "******************************++a****************************" << endl;
	//mas3 = ++mas1;
	//mas1.Print();
	//mas3.Print();
	//cout << "******************************a++****************************" << endl;
	//mas3 = mas1++;
	//mas1.Print();
	//mas3.Print();
	//cout << "**********************порівняння обєктів ==*********************" << endl;
	//if (mas1 == mas2) cout << "yes" << endl; // бінарна операція, порівняння двох обєктів
	//else cout << "no" << endl;
	//cout << "**********************порівняння обєктів !=*********************" << endl;
	//if (mas1 == mas2) cout << "yes" << endl;
	//else cout << "no" << endl;
	//cout << "**********************порівняння обєктів <*********************" << endl;
	//if (mas1 < mas2) cout << "yes" << endl;
	//else cout << "no" << endl;
	//cout << "**********************mas1[1] = 10;*********************" << endl;
	//mas1[1] = 10;
	//cout << mas1[1] << endl;
	//// 19.06.2020
	//cout << "***************************19.06.2020******************************" << endl;
	//mas1.Print();
	//cout << "**************************** << *****************************" << endl;
	///*
	//a=3;
	//a<<1; - 6
	//*/
	//cout << "mas1" << endl;
	//cout << mas1; // бінарна операція
	//cout << "mas1, mas2" << endl;
	//cout << mas1 << mas2 << endl; // бінарна операція
	//cout << "****************************** >> ***************************" << endl;
	///*
	//cin >> mas1;
	//cout << mas1;
	//*/
	//cout << "*********************************************************" << endl;
	/*Array P = foo();
	cout << P;
	cout << "\nThe end\n";*/
	/*
	cout << "*********************************************************" << endl;
	Array P(3);
	P = foo();
	cout << "\nThe end\n";
	*/
	cout << "*********************************************************" << endl;
	cout << "before sort" << endl;
	cout << mas2;
	cout << "after sort" << endl;
	mas2.QuicksSort();
	cout << mas2;

}