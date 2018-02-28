#pragma once
#include <iostream>
class AbstractTemplate
{
public:
	AbstractTemplate() {
	}
	virtual ~AbstractTemplate() {
	}

	virtual void Create() = 0;
	virtual void Assign() = 0;
	virtual void Using() = 0;
	virtual void Destory() = 0;

	void Process() {
		Create();
		Assign();
		Using();
		Destory();
	}
};

class TemplateA : public AbstractTemplate
{
public:
	TemplateA() {
	}
	~TemplateA() {
	}

	void Create() {
		std::cout << "A Template A has been Created" << std::endl;
	}
	void Assign() {
		std::cout << "A Template A has been Assigned" << std::endl;
	}
	void Using() {
		std::cout << "A Template A has been Used" << std::endl;
	}
	void Destory() {
		std::cout << "A Template A has been Destroyed" << std::endl;
	}
};

class TemplateB : public AbstractTemplate
{
public:
	TemplateB() {
	}
	~TemplateB() {
	}

	void Create() {
		std::cout << "A Template B has been Created" << std::endl;
	}
	void Assign() {
		std::cout << "A Template B has been Assigned" << std::endl;
	}
	void Using() {
		std::cout << "A Template B has been Used" << std::endl;
	}
	void Destory() {
		std::cout << "A Template B has been Destroyed" << std::endl;
	}
};