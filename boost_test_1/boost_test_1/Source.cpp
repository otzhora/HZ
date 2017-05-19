#define _CRT_SECURE_NO_WARNINGS
#include <boost/regex.hpp>
#include <iostream>
#include <string>


int main()
{
	std::freopen("jane.txt", "rt", stdin);
	std::freopen("out.txt", "wt", stdout);
	std::string line;
	boost::regex pat("^Subject: (Re: |Aw: )*(.*)");

	while (std::cin)
	{
		std::getline(std::cin, line);
		boost::smatch matches;
		if (boost::regex_match(line, matches, pat))
			std::cout << matches[2] << std::endl;
	}
}