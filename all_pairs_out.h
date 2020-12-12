#pragma once

#include <utility>


// output all pairs in range to output iterator

template <class Out, class IT, class End=IT>
void all_pairs_out(Out out, IT begin, End end)
{
	if (begin == end)
		return;

	for (IT it = begin++; begin != end; ++begin != end || ++(begin = ++it))
		*out++ = std::make_pair(*it, *begin);
}


template <class Out, class C>
auto all_pairs_out(Out out, C &&c)
  -> decltype(all_pairs_out(out, c.begin(), c.end()))
{ return      all_pairs_out(out, c.begin(), c.end()); }


