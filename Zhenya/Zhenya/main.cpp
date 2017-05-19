#include "tree.h"
#include <vector>
#include <map>
#include <cstring>
#include <iostream>
int main()
{
	{
		Tree<int> loliruy_s_tebya;
		std::vector<int> a(8);
		a[0] = 0;
		a[1] = 2;
		a[2] = 1;
		a[3] = 4;
		a[4] = -4;
		a[5] = 2;
		a[6] = 4;
		a[7] = 16;
		loliruy_s_tebya.add(a[0]);
		loliruy_s_tebya.add(a[1]);
		loliruy_s_tebya.add(a[2]);
		loliruy_s_tebya.add(a[3]);
		loliruy_s_tebya.add(a[4]);
		loliruy_s_tebya.print();
		std::cout << loliruy_s_tebya.find(a[5]) << std::endl;
		std::cout << loliruy_s_tebya.find(a[6]) << std::endl;
		std::cout << loliruy_s_tebya.find(a[7]) << std::endl;
		Tree<int>::iterator iter = loliruy_s_tebya.getroot();
		std::cout << iter.getval() << std::endl;
		iter++;
		std::cout << iter.getval() << std::endl;
		iter++;
		std::cout << iter.getval() << std::endl;
		
	}
	system("pause");
	return 0;
}