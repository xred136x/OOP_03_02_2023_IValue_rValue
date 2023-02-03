#include<iostream>
#include<map>
#include<algorithm>
// lValue, rValue, ссылки и универсальные ссылки 
// copy-swap, принцип

int foo() {
	return 2;
}

int globalvalue = 20; // lvalue объект который занимает идентифицируемое место в пам€ти(имеет адрес и т.д)
int& bar() {
	return globalvalue;
}

class A {
public:
	void foo()const {
		std::cout << "A::foo() const\n";
	}
	void foo() {
		std::cout << "A::foo()\n";
	}
};

A aFunc() { return A(); }
const A c_aFunc() { return A(); }



class Intvec {
public:
	explicit Intvec(size_t num = 0) : m_size(num), m_data(new int[m_size]) {
		log("constructor");
	}
	~Intvec() {
		log("destructor");
		if (m_data) {
			delete m_data;
			m_data = nullptr;
		}
	}
	Intvec(const Intvec& other) : m_size(other.m_size),	m_data(new int[m_size]) {
		log("copy constructor");
		for (size_t i = 0; i < m_size; i++) {
			m_data[i] = other.m_data[i];
		}
	}

	Intvec& operator=(Intvec &&other) noexcept {// &&-ссылка на rvalue
		// оператор присваивани€ перемещением
		log("move assigment operator");
		std::swap(m_size, other.m_size);
		std::swap(m_data, other.m_data);
		return *this;
	}
	// c1 = c2
	Intvec& operator=(const Intvec& other) {
		// оператор присваивани€ копированием
		log("copy assigment operator");
		Intvec tmp(other);
		std::swap(m_size, tmp.m_size);
		std::swap(m_data, tmp.m_data);
		return *this;
	}

	
private:
	void log(const char* msg) {
		std::cout << "[" << this << ']' << msg << '\n';
	}
		size_t m_size;
		int* m_data;
};

int main() {

	setlocale(LC_ALL, "ru");

	/*aFunc().foo();
	c_aFunc().foo();*/

	int x = 5;
	//foo() = 2;
	bar() = 10;

	std::map<int, float> mymap;
	mymap[10] = 5.6f;// operator[] внутри класса std::map который вернул ссылку на объект, который можно измен€ть
 
	const int a = 10;
	//a = 2; не возможно присваивание

	int t = 1;
	int tt = 2;
	int res = t + tt;// operator+ ожидает rvalue, пoэтому lvalue не€вно преобразуетс€ в rvalue
	
	int arr[] = { 1,2,3 };
	int* p = &arr[0];
	*(p + 1) = 10; // €вное преобразование rvalue (p+1) в lvalue спомощью * // *(p+1)- lvalue
	
	// ivalue в rvalue с помощью &

	int var = 10;
	//int* bad_addr = &(var + 1);// error: дл€ унарного оператора & требуетс€ lvalue

	int* addr = &var;// ok
	//&var = 40;// error: с левой стороны требуетс€ lvalue
	*addr = 40;// дома проверить

	//lvalue на тип “, не €вл€етс€ функциональным или массивом, может быть преобразован в rvalue<...>
	//если “ не класс, типом рвалуе €вл€етс€ cv-неспецифированна€ верси€ типа “. иначе типом рвалуе €вл€етс€ 
	// cv: c - const, v - volatile
	//  если “ это класс то рвалуе можее сохранить cv- специфицированность, т.е может быть const || volatile, || const && volatile


	Intvec v1(20);
	Intvec v2;
	Intvec v3;

	std::cout << "assigning Ivalue...\n";
	v2 = v1;
	std::cout << "ended assigning lvalue...\n";
	std::cout << "===========================\n";
	std::cout << "assigning rvalue...\n";
	v3 = Intvec(33);
	v3 = std::move(v1);// std::move принимает lvalue, возвращает rvalue (опасна€ штука)
	std::cout << "ended assigning rvalue...\n";
	return 0;
}