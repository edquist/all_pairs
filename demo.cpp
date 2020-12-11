#include "all_pairs.h"
#include <initializer_list>
#include <iostream>

void demo1()
{
	auto list = { 1,2,3,4,99 };
	for (auto &&x : all_pairs(list) )
		std::cout << x.first << "\t" << x.second << "\n";
}

void demo2()
{
	// c++17 - range-for loop semantics (begin/end can be different types)

	auto list = { 1,2,3,4,99 };
	auto &&range = all_pairs(list);
	auto begin = range.begin();
	auto end = range.end2();  // the end sentinal version
	for ( ; begin != end; ++begin) {
		auto &&x = *begin;
		std::cout << x.first << "\t" << x.second << "\n";
	}
}

int main()
{
	demo1();

	std::cout << "\n----------\n\n";

	demo2();
}
