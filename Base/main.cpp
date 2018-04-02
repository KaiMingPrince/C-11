#include "thread.hpp"
int main(int agrc, char* argv[])
{
	double i = 10;
	double& r = i;
	int s = sizeof(r);
	getchar();
	return 0;
}