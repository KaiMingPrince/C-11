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

class VirtualBase {
public:
	virtual void f() {
		std::cout << "VirtualBase::f()" << std::endl;
	}
};
class VirtualDerived : public VirtualBase
{
public:
	virtual void f() {
		std::cout << "VirtualDerived::f()" << std::endl;
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
	double d = 9.02;
	double* pd = &d;
	int* pi_re = reinterpret_cast<int*>(pd);
	//int i_re = reinterpret_cast<int>(d);//不能转换非指针对象
	std::cout << *pi_re << std::endl;
	int i_static = static_cast<int>(d);	//基本类型的强转
	std::cout << i_static << std::endl;

	VirtualDerived dervied;
	VirtualBase& base = static_cast<VirtualBase&>(dervied);//继承关系的转换
	base.f();

// 	Derived* dervied_ptr = new Derived;
// 	Base* base_ptr = dynamic_cast<Base*>(dervied_ptr);	//非多态只能往下转换
// 	base_ptr->f();

// 	VirtualBase* base_ptr = new VirtualBase;
// 	//多态可以往上转换，但是可能无效
// 	VirtualDerived* dervied_ptr = dynamic_cast<VirtualDerived*>(base_ptr);	
// 	if (dervied_ptr)
// 		dervied_ptr->f();
}