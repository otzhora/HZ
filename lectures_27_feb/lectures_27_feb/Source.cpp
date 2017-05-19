#include <iostream>
#include "complex.h"

using  namespace std;

int main()
{
	Complex c1(1,1), c2(2,4);
	print(c1.add(c2));
	print(c1);
	system("pause");
	return 0;
}