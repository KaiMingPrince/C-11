#pragma once
#include "SimpleFactory.h"

class FactoryInterface
{
public:
	FactoryInterface() {
	}
	virtual ~FactoryInterface() {
	}

	virtual std::shared_ptr<ButtonInterface> CreateButton() = 0;
	virtual std::shared_ptr<LabelInterface> CreateLabel() = 0;
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
	std::shared_ptr<LabelInterface> CreateLabel() {
		return std::make_shared<LabelA>();
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
	std::shared_ptr<LabelInterface> CreateLabel() {
		return std::make_shared<LabelB>();
	}
};
