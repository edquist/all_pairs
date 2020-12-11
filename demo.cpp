#include "all_pairs.h"
#include <initializer_list>
#include <iostream>

template <class ...Arg>
void print_range_for_pairs(Arg &&...arg)
{
	for (auto &&x : all_pairs(std::forward<Arg>(arg)...) )
		std::cout << x.first << "\t" << x.second << "\n";
}

template <class ...Arg>
void print_range_for_pairs2(Arg &&...arg)
{
	// c++17 - range-for loop semantics (begin/end can be different types)

	auto &&range = all_pairs(std::forward<Arg>(arg)...);
	auto begin   = range.begin();
	auto end     = range.end2();  // the end sentinal version
	for ( ; begin != end; ++begin) {
		auto &&x = *begin;
		std::cout << x.first << "\t" << x.second << "\n";
	}
}


void demo1()
{
	auto list = { 1,2,3,4,99 };
	print_range_for_pairs(list);
}

void demo2()
{
	auto list = { 1,2,3,4,99 };
	print_range_for_pairs2(list);
}

void demo3()
{
	auto list = { 'a', 'b', 'c', 'd' };
	print_range_for_pairs(list);
}

void demo4()
{
	const char *s = "abcd";
	print_range_for_pairs(s, s+4);
}

struct cstr_end {};

bool operator==(const char *p, cstr_end) { return *p == 0; }
bool operator!=(const char *p, cstr_end) { return *p != 0; }


void demo5()
{
	// all pairs for string with end sentinal
	print_range_for_pairs2("abcd", cstr_end{});
}

void spacer() { std::cout << "\n----------\n\n"; }

int main()
{
	demo1(); spacer();
	demo2(); spacer();
	demo3(); spacer();
	demo4(); spacer();
	demo5(); spacer();
}

