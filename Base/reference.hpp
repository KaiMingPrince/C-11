#pragma once
#include <iostream>
#include <vector>

class right_value_class {
	char* m_str = nullptr;
public:
	right_value_class() {
		std::cout << "Construct without arguments" << std::endl;
	}
	right_value_class(char* pStr) : m_str(pStr) {

	}
	~right_value_class() {
		if (m_str) delete [] m_str;
	}
	right_value_class(right_value_class& other) {
		std::cout << "Construct with left reference value" << std::endl;
		m_str = new char[strlen(other.m_str) + 1];
		memset(m_str, 0, strlen(other.m_str) + 1);
		strcpy_s(m_str, strlen(other.m_str)+1, other.m_str);
	}
	right_value_class(right_value_class&& other) {
		std::cout << "Construct with right reference value" << std::endl;
		m_str = other.m_str;
		other.m_str = nullptr;
	}
	right_value_class& operator = (right_value_class& other) {
		std::cout << "Assignment with left reference value" << std::endl;
		if (this != &other) {
			if (m_str) delete [] m_str;
			m_str = new char[strlen(other.m_str) + 1];
			memset(m_str, 0, strlen(other.m_str) + 1);
			strcpy_s(m_str, strlen(other.m_str)+1, other.m_str);
		}
		return *this;
	}
	right_value_class& operator = (right_value_class&& other) {
		std::cout << "Assignment with right reference value" << std::endl;
		if (this != &other) {
			if (m_str) delete [] m_str;
			m_str = other.m_str;
			other.m_str = nullptr;
		}
		return *this;
	}

	void PrintHeapObjectAddress() {
		std::cout << "m_str's address is " << static_cast<const void *>(m_str) << std::endl;
	}
};

void test_right_value_reference() {
	right_value_class r1;
	char *pStr = new char[100];
	memset(pStr, 0, 100);
	strcpy_s(pStr, 100, "test right value reference");
	right_value_class r2(pStr);
	r2.PrintHeapObjectAddress();
	r1 = r2;
	r1.PrintHeapObjectAddress();
	r1 = std::move(r2);
	r1.PrintHeapObjectAddress();
	right_value_class r3(r1);
	r3.PrintHeapObjectAddress();
	right_value_class r4(std::move(r1));
	r4.PrintHeapObjectAddress();
}

class SimpleReference {
private:
	char& m_r;
};

//��ӡ��֪��ֻ��һ�����ö�����࣬size��СΪ4����ֻ��һ��ָ�������һ����
void PrintSimpleReference(){
	std::cout << "Size of the class with a simple reference is " << sizeof(SimpleReference) << std::endl;
}

//�ӵ��õķ�������������ָ�������ʹ������ͬ�Ļ������
void ReferencePointerTest() {
	int i = 100;
	int *pi = &i;
	std::cout << "Pointer Value is " << *pi << std::endl;
	int& ri = i;
	std::cout << "Reference Value is " << ri << std::endl;
}

//������һ����ֵ���ã�����д����ֵ���û����ʧ��
void ReferenceArgTest(int& ri) {
	std::cout << "Reference Argument is " << ri << std::endl;
}

//������һ��const��ֵ���ã�������ֵ��ֵ����д��
void ConstReferenceArgTest(const int& cri) {
	std::cout << "Const Reference Argument is " << cri << std::endl;
}

void ConstReferenceTest() {
	int i = 100;
	const int ci = 110;
	const int& rci0 = i;
	const int& rci1 = ci;
	const int& rci2 = 120;
	std::cout << "rci0 " << rci0 << " rci1 " << rci1 << " rci2 " << rci2;
	//ReferenceArgTest(100);
	ConstReferenceArgTest(100);
}

class BaseClass {
public:
	BaseClass() : m_vBuff(10000, 'a') {
		std::cout << "Construct BaseClass" << std::endl;
	}
	BaseClass(const BaseClass& other) {
		m_vBuff = other.m_vBuff;
		std::cout << "Copy BaseClass" << std::endl;
	}
	BaseClass& operator=(const BaseClass& other) {
		if (this != &other) {
			m_vBuff = other.m_vBuff;
		}
		std::cout << "Assign BaseClass" << std::endl;
		return *this;
	}
	BaseClass(BaseClass&& other) {
		m_vBuff = std::move(other.m_vBuff);//ת��Ϊ��ֵ���ú󣬻��Զ�����vector���ƶ���ֵ
		std::cout << "Move BaseClass" << std::endl;
	}
	BaseClass& operator=(BaseClass&& other) {
		m_vBuff = std::move(other.m_vBuff);
		std::cout << "Move Assign BaseClass" << std::endl;
		return *this;
	}
	~BaseClass() {
		std::cout << "Destruct BaseClass" << std::endl;
	}
	
private:
	std::vector<char>		m_vBuff;
};

BaseClass Create() {
	return BaseClass();
}

void BaseClassTest() {
	BaseClass b;
	b = Create();
}

void Print(const BaseClass& b) {
	std::cout << "Print BaseClass by Left Reference" << std::endl;
}

void Print(BaseClass&& b) {
	std::cout << "Print BaseClass by  Right Reference" << std::endl;
}

void PrePrint(BaseClass&& b) {
	Print(b);
}

void ForwardPrint(BaseClass&& b) {
	Print(std::forward<BaseClass>(b));
}

void SimpleAssignTest() {
	BaseClass b1;
	PrePrint(std::move(b1));
	ForwardPrint(std::move(b1));
}

template<class T>
void TemplateReferenceCollapsing(T&& t) {
	if (std::is_same<BaseClass, T>::value) {
		std::cout << "T is the BaseClass type" << std::endl;
	}
	else if (std::is_same<BaseClass&, T>::value) {
		std::cout << "T is the BaseClass& type" << std::endl;
	}
	else if (std::is_same<BaseClass&&, T>::value) {
		std::cout << "T is the BaseClass&& type" << std::endl;
	}
	Print(std::forward<T>(t));
}

void ReferenceCollapsingTest() {
	BaseClass b;
	BaseClass &rb = b;
	TemplateReferenceCollapsing(b);
	TemplateReferenceCollapsing(rb);
	TemplateReferenceCollapsing(Create());
}

template <class T>
class ForwardClass {
public:
	void Print(T& t) {
		std::cout << "Print Left Value" << std::endl;
	}
	void Print(T&& t) {
		std::cout << "Print Right Value" << std::endl;
	}
};

void FowardClassTest() {
	ForwardClass<int> f;
	int i = 100;
	f.Print(i);
}