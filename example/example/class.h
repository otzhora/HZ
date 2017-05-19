#pragma once
#include <vector>


template<typename T>
class biec
{
public:

	biec()
	{}

	void add(T x, T y)
	{
		for (int i = 0; i < arr_X_Y.size(); i++)
		{
			if (arr_X_Y[i].first == x || arr_Y_X[i].first == y)
				throw "Element is already on biec";
		}
		arr_X_Y.push_back(std::make_pair(x, y));
		arr_Y_X.push_back(std::make_pair(y, x));
	}


	std::pair<T, T> getPairX(T x)
	{
		for (int i = 0; i < arr_X_Y.size(); i++)
		{
			if (arr_X_Y[i].first == x)
				return(arr_X_Y[i]);
		}
		throw "Element not in biec";
	}

	std::pair<T, T> getPairY(T y)
	{
		for (int i = 0; i < arr_Y_X.size(); i++)
		{
			if (arr_Y_X[i].first == y)
				return(arr_Y_X[i]);
		}
		throw "Element not in biec";
	}
	~biec()
	{
		arr_X_Y.clear();
		arr_Y_X.clear();
	}
private:

	std::vector< std::pair<T, T> > arr_X_Y;
	std::vector< std::pair<T, T> > arr_Y_X;
};

template<> class biec <char>
{
public:
	biec()
	{}

	void add(char x, char y)
	{
		std::cout << x << " " << y << " ";
		if (int(x) < 97)
			x = char(int(x) + 32);

		if (int(y) < 97)
			y = char(int(y) + 32);
		std::cout << x << " " << y << " ";
		for (int i = 0; i < arr_X_Y.size(); i++)
		{
			if (arr_X_Y[i].first == x || arr_Y_X[i].first == y || arr_X_Y[i].second == y || arr_X_Y[i].first == x)
				throw "Element is already on biec";
		}


		arr_X_Y.push_back(std::make_pair(x, y));
		arr_Y_X.push_back(std::make_pair(y, x));
	}


	std::pair<char, char> getPairX(char x)
	{

		if (int(x) < 97)
			x = char(int(x) + 34);
		for (int i = 0; i < arr_X_Y.size(); i++)
		{
			if (arr_X_Y[i].first == x)
				return(arr_X_Y[i]);
		}
		throw "Element not in biec";
	}

	std::pair<char, char> getPairY(char y)
	{

		if (int(y) < 97)
			y = char(int(y) + 34);
		for (int i = 0; i < arr_Y_X.size(); i++)
		{
			if (arr_Y_X[i].first == y)
				return(arr_Y_X[i]);
		}
		throw "Element not in biec";
	}
	~biec()
	{
		arr_X_Y.clear();
		arr_Y_X.clear();
	}
private:
	std::vector < std::pair<char, char> > arr_X_Y;
	std::vector < std::pair<char, char> > arr_Y_X;
};