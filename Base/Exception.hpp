#pragma once
#include <iostream>
class Base {
public:
	virtual void f() {
		std::cout << "Base::f()" << std::endl;
	}
};
class Derived : public Base
{
public:
	virtual void f() {
		std::cout << "Derived::f()" << std::endl;
	}
};

class Other
{
public:
	virtual void f() {
		std::cout << "Other::f()" << std::endl;
	}
};

void bad_cast_throw()
{
	Other o;
	try
	{
		Derived& derived_ref = dynamic_cast<Derived&>(o);
	}
	catch (const std::bad_cast& e)	
	{
		std::cout << e.what() << std::endl;
	}
}