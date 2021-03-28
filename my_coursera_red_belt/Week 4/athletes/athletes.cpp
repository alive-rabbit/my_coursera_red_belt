#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include "profile.h"

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	const int MAX_ATHLETES = 100'000;
	size_t quantity_of_operations = 0;
	std::cin >> quantity_of_operations;
	
	std::list<int> athletes;
	std::vector<std::list<int>::iterator> athletes_pos (MAX_ATHLETES + 1, athletes.end());
	for (size_t i = 0; i < quantity_of_operations; i++)
	{
		int first_athlet, second_athlet;
		std::cin >> first_athlet >> second_athlet;
		athletes_pos[first_athlet] = athletes.insert(athletes_pos[second_athlet], first_athlet);
	}
	for (const int& el : athletes)
	{
		std::cout << el << '\n';
	}
	return 0;
}
