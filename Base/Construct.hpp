#pragma once
#include <iostream>  
#include <assert.h>  
using namespace std;

class Temp
{
public:
	Temp(const char* str = nullptr);
	Temp(Temp&& t);
	Temp& operator = (Temp&& t);
	Temp(const Temp& t);
	Temp& operator = (Temp& t);
	~Temp(void);
private:
	char *m_pData;
};

Temp::Temp(const char* str)
{
	if (!str)
	{
		m_pData = nullptr;
	}
	else
	{
		this->m_pData = new char[strlen(str) + 1];
		strcpy(this->m_pData, str);
	}
}

Temp::Temp(Temp&& t) :m_pData(move(t.m_pData))
{
	t.m_pData = nullptr;
}

Temp& Temp::operator = (Temp&& t)
{
	assert(this != &t);
	if (m_pData)
		delete m_pData;
	this->m_pData = move(t.m_pData);
	t.m_pData = nullptr;

	return *this;
}

Temp::Temp(const Temp& t)
{
	if (!t.m_pData)
	{
		this->m_pData = nullptr;
	}
	else
	{
		this->m_pData = new char[strlen(t.m_pData) + 1];
		strcpy(this->m_pData, t.m_pData);
	}
}

Temp& Temp::operator = (Temp &t)
{
	if (this != &t)
	{
		delete[] this->m_pData;
		if (!t.m_pData)
		{
			this->m_pData = nullptr;
		}
		else
		{
			this->m_pData = new char[strlen(t.m_pData) + 1];
			strcpy(this->m_pData, t.m_pData);
		}
	}

	return *this;
}

Temp::~Temp(void)
{
	if (this->m_pData)
	{
		delete[] this->m_pData;
		this->m_pData = nullptr;
	}
}