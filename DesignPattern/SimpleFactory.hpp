#pragma once
#include <iostream>
#include <memory>
#include <string>
class ButtonInterface
{
public:
	ButtonInterface() {
	}
	virtual ~ButtonInterface() {
	}

	virtual void onClicked() = 0;
	virtual void onChecked(bool bChecked) = 0;
};

class ButtonA : public ButtonInterface
{
public:
	ButtonA() {
	}
	~ButtonA() {
	}

	virtual void onClicked() {
		std::cout << "ButtonA has been Clicked" << std::endl;
	}
	virtual void onChecked(bool bChecked) {
		std::cout << "ButtonA has been " << (bChecked ? "Checked" : "UnChecked") << std::endl;
	}
};

class ButtonB : public ButtonInterface
{
public:
	ButtonB() {
	}
	~ButtonB() {
	}

	virtual void onClicked() {
		std::cout << "ButtonB has been Clicked" << std::endl;
	}
	virtual void onChecked(bool bChecked) {
		std::cout << "ButtonB has been " << (bChecked ? "Checked" : "UnChecked") << std::endl;
	}
};

class LabelInterface
{
public:
	LabelInterface() {
	}
	virtual ~LabelInterface() {
	}

	virtual void setText(const std::string& strText) = 0;
};

class LabelA : public LabelInterface
{
public:
	LabelA() {
	}
	~LabelA() {
	}

	virtual void setText(const std::string& strText) {
		std::cout << "LabelA's Text has been set " << strText << std::endl;
	}
};

class LabelB : public LabelInterface
{
public:
	LabelB() {
	}
	~LabelB() {
	}

	virtual void setText(const std::string& strText) {
		std::cout << "LabelB's Text has been set " << strText << std::endl;
	}
};

class Factory
{
public:
	std::shared_ptr<ButtonInterface> CreateButton(const std::string& strType) {
		if ("A" == strType)
			return std::make_shared<ButtonA>();
		else if ("B" == strType)
			return std::make_shared<ButtonB>();
		else
			return nullptr;
	}
};
