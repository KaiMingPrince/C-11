#pragma once
template <class T>
class Singleton
{
private:
	Singleton() {
	}
	~Singleton() {
	}

public:
	static T& Instance() {
		static T object;
		return object;
	}
};