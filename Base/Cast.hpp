#pragma once
#include <iostream>

class Base {
public:
	void f() {
		std::cout << "Base::f()" << std::endl;
	}
};
class Derived : public Base
{
public:
	void f() {
		std::cout << "Derived::f()" << std::endl;
	}
};

void TestDemo()
{
	Base* base_ptr = new Base;
	Derived* dervied_ptr = new Derived;
	base_ptr = dynamic_cast<Base*>(dervied_ptr);
	base_ptr->f();
}