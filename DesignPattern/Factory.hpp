#include "SimpleFactory.h"

class FactoryInterface
{
public:
	FactoryInterface() {
	}
	virtual ~FactoryInterface() {
	}

	virtual std::shared_ptr<ButtonInterface> CreateButton() = 0;
};

class FactoryA : public FactoryInterface
{
public:
	FactoryA() {
	}
	virtual ~FactoryA() {
	}

	std::shared_ptr<ButtonInterface> CreateButton() {
		return std::make_shared<ButtonA>();
	}
};

class FactoryB : public FactoryInterface
{
public:
	FactoryB() {
	}
	virtual ~FactoryB() {
	}

	std::shared_ptr<ButtonInterface> CreateButton() {
		return std::make_shared<ButtonB>();
	}
};