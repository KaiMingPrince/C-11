#pragma once
#include <iostream>
class StrategyInterface
{
public:
	StrategyInterface() {
	}
	virtual ~StrategyInterface() {
	}

	virtual void Implement() = 0;
};

class StrategyAdmin : public StrategyInterface
{
public:
	StrategyAdmin() {
	}
	~StrategyAdmin() {
	}
	void Implement() {
		std::cout << "This is the Implement of Admin" << std::endl;
	}
};

class StrategyUser : public StrategyInterface
{
public:
	StrategyUser() {
	}
	~StrategyUser() {
	}
	void Implement() {
		std::cout << "This is the Implement of User" << std::endl;
	}
};

class Client
{
public:
	Client(StrategyInterface& ref) : m_refStrategy(ref) {
	}
	~Client() {
	}

	void Invoke() {
		m_refStrategy.Implement();
	}

private:
	StrategyInterface& m_refStrategy;
};

