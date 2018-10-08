#pragma once
#include <iostream>
#include <memory>
template<class T>
class IntellPointer {
public:
	IntellPointer() : m_pointer(nullptr), m_ref_count_ptr(new uint32_t(1)) {
	}
	IntellPointer(T* other) : m_pointer(other), m_ref_count_ptr(new uint32_t(1)) {
	}
	IntellPointer(const IntellPointer<T>& other) : m_pointer(other.m_pointer), m_ref_count_ptr(other.m_ref_count_ptr){
		++(*m_ref_count_ptr);
	}
	~IntellPointer() {
		if (0 == --(*m_ref_count_ptr)) {
			if (m_pointer)
				delete m_pointer;
			delete m_ref_count_ptr;
		}
	}

	IntellPointer& operator = (T* other) {
		m_pointer = other;
		//脱离了原来的内存管理
		if (0 == --(*m_ref_count_ptr)) {
			if (m_pointer)
				delete m_pointer;
			delete m_ref_count_ptr;
		}
		m_ref_count_ptr = new uint32_t(1);
		return *this;
	}
	IntellPointer& operator = (const IntellPointer<T>& other) {
		if (0 == --*(m_ref_count_ptr)) {
			if (m_pointer)
				delete m_pointer;
			delete m_ref_count_ptr;
		}
		m_pointer = other.m_pointer;
		m_ref_count_ptr = other.m_ref_count_ptr;
		++(*m_ref_count_ptr);
		return *this;
	}

	friend T operator*(const IntellPointer<T>& other) {
		return *(other.m_pointer);
	}

	uint32_t ref_count() const {
		return *m_ref_count_ptr;
	}

private:
	T*			m_pointer;
	uint32_t*	m_ref_count_ptr;
};

void TestDemo() {
	IntellPointer<int> itell(new int(10));
	IntellPointer<int> itell2 = itell;
	std::cout << *itell2 << std::endl;
}


void TestStandardIntellPointer() {
	std::shared_ptr<int> ptr1 = std::make_shared<int>(100);
	std::cout << "ptr use count is " << ptr1.use_count() << std::endl;
	auto ptr2 = ptr1;
	std::cout << "ptr use count is " << ptr1.use_count() << std::endl;
	std::unique_ptr<int> un_ptr1 = std::make_unique<int>(200);
	auto un_ptr2 = std::move(un_ptr1);
	std::cout << "now unique ptr1's address is " << static_cast<const void*>(un_ptr1.get()) << std::endl;

	//shared不能直接使用数组做模板参，要管理数组只能自己加回收接口，unique可以直接使用
	std::shared_ptr<int> arr_shared_ptr(new int[128], [](int* p) {delete[]p; });
	std::unique_ptr<char[]> arr_ptr(new char[128]);
}