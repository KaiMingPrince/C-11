#pragma once
#include <memory>
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

class Extras
{
public:
	void f() {
		std::cout << "Extras::f()" << std::endl;
	}
};

void TestDemo()
{
	std::shared_ptr<Base> base_ptr = std::make_shared<Base>();
	std::shared_ptr<Derived> dervied_ptr = std::make_shared<Derived>();
	std::shared_ptr<Extras> extra_ptr = std::make_shared<Extras>();
	base_ptr = std::dynamic_pointer_cast<Base>(dervied_ptr);
	base_ptr->f();
}