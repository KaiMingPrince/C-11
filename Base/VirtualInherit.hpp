#pragma once
#include <iostream>
#include <cassert>
#pragma vtordisp(off)	//on状态会多出4字节在Base类虚函数表之前，其值为0
//cl.exe 可以查看类内存布局 cl filename.cpp //d1reportSingleClassLayout[ClassName]

class Base
{
private:
	int m_nBase;
public:
	Base() : m_nBase(1){
	}

	virtual void f() { 
		std::cout << "Base::f()" << std::endl;
	}
	virtual void base_f() {
		std::cout << "Base::base_f()" << std::endl; 
	}
};

class VirtualBaseOne : virtual public Base
{
private:
	int m_nVirtualBaseOne;
public:
	VirtualBaseOne() :m_nVirtualBaseOne(11){
	}

	virtual void f() { 
		std::cout << "VirtualBaseOne::f()" << std::endl; 
	}
	virtual void base_one() { 
		std::cout << "VirtualBaseOne::base_one()" << std::endl; 
	}
	virtual void virtual_base_one() { 
		std::cout << "VirtualBaseOne::virtual_base_one()" << std::endl; 
	}
};

class VirtualBaseTwo : virtual public Base
{
private:
	int m_nVirtualBaseTwo;
public:
	VirtualBaseTwo() :m_nVirtualBaseTwo(22) {
	}

	virtual void f() { 
		std::cout << "VirtualBaseTwo::f()" << std::endl; 
	}
	virtual void base_two() { 
		std::cout << "VirtualBaseTwo::base_two()" << std::endl; 
	}
	virtual void virtual_base_two() { 
		std::cout << "VirtualBaseTwo::virtual_base_two()" << std::endl; 
	}
};

class Inherit : public VirtualBaseOne, public VirtualBaseTwo
{
private:
	int m_nInherit;
public:
	Inherit() :m_nInherit(100){
	}

	virtual void f() { 
		std::cout << "Inherit::f()" << std::endl; 
	}
	virtual void virtual_base_one() { 
		std::cout << "Inherit::virtual_base_one()" << std::endl; 
	}
	virtual void virtual_base_two() { 
		std::cout << "Inherit::virtual_base_two()" << std::endl; 
	}
	virtual void inherit() { 
		std::cout << "Inherit::Inherit()" << std::endl; 
	}

	typedef void (*fptr)();
	void TestDemo() {
		int* obj_ptr = (int*)this;
		int* base_one_vf_ptr = obj_ptr;
		((fptr)(*(((int*)*base_one_vf_ptr))))();
		((fptr)(*(((int*)*base_one_vf_ptr)+1)))();
		((fptr)(*(((int*)*base_one_vf_ptr) + 2)))();
		int* base_one_vb_ptr = obj_ptr + 1;
		std::cout << "Inherit::base_one virtual base table and base_one class offset is " << *(int*)(*base_one_vb_ptr) << std::endl;
		std::cout << "Inherit::base_one virtual base table and base class offset is " << *((int*)(*base_one_vb_ptr)+1) << std::endl;
		std::cout << "Inherit::base_one virtual base table end value " << *((int*)(*base_one_vb_ptr) + 2) << std::endl;
		std::cout << "Inherit::m_nVirtualBaseOne is " << *(obj_ptr + 2) << std::endl;
		int* base_two_vf_ptr = obj_ptr + 3;
		((fptr)(*(((int*)*base_two_vf_ptr))))();
		((fptr)(*(((int*)*base_two_vf_ptr) + 1)))();
		int* base_two_vb_ptr = obj_ptr + 4;
		assert((int*)(*base_two_vb_ptr) == (int*)(*base_one_vb_ptr) + 3);
		assert((int*)(*base_two_vb_ptr)+1 == (int*)(*base_one_vb_ptr) + 4);
		std::cout << "Inherit::m_nVirtualBaseTwo is " << *(obj_ptr + 5) << std::endl;
		std::cout << "Inherit::m_nInherit is " << *(obj_ptr + 6) << std::endl;
		int *base_vf_ptr = obj_ptr + 7;
		((fptr)(*(((int*)*base_vf_ptr))))();
		((fptr)(*(((int*)*base_vf_ptr)+1)))();
		std::cout << "Inherit::m_nBase is " << *(obj_ptr + 8) << std::endl;
		std::cout << "Inherit Size is " << sizeof(Inherit) << std::endl;
	}
};