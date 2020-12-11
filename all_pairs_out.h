#pragma once

#include <utility>


// output all pairs in range to output iterator

template <class Out, class IT, class End=IT>
void all_pairs_out(Out out, IT begin, End end)
{
	if (begin == end)
		return;

	IT it1 = begin;
	++begin;

	while (begin != end) {
		*out++ = std::make_pair(*it1, *begin);

		if (++begin == end)
			++(begin = ++it1);
	}
}


template <class Out, class C>
auto all_pairs_out(Out out, C &&c)
  -> decltype(all_pairs_out(out, c.begin(), c.end()))
{ return      all_pairs_out(out, c.begin(), c.end()); }


