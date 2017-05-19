#include <iostream>
#include <string>
#include <fstream>
#include <io.h>
#include "class.h"
using namespace std;


int main()
{
	biec<char> a;
	try {
		a.add('c', 'D');
		a.add('d', 'b');
		pair<char, char> abc;
		abc = a.getPairY('D');
		cout << abc.first << " " << abc.second << endl;
	}
	catch (char* c)
	{
		cout << c << endl;
	}

	system("pause");
}
