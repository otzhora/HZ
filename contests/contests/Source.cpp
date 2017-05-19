#define _CRT_SECURE_NO_WARNINGS
#define mp(a, b) make_pair(a, b)
#define all(a) a.begin(), a.end()
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <set>
#include "message.h"

typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<bool> vb;
typedef std::vector<long long> vll;
typedef std::vector< std::pair<int, int> > vpii;
typedef std::vector< std::string > vs;

using namespace std;

int main(int argc, char** argv)
{
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);

	map<char*, char*> names;
	char* id = "0003\0";
	char* nick = "mat' shluha\0";

	names[id] = nick;
	
	char* new_id = "0005\0";
	char* new_nick = "rot ebal\0";
	names[new_id] = new_nick;
	for (auto i = names.begin(); i != names.end(); i++)
		cout << i->first << " " << i->second << endl;
	return 0;
}