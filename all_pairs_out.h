#pragma once

#include <utility>


// output all pairs in range to output iterator

template <class Out, class IT, class End=IT>
void all_pairs_out(Out out, IT begin, End end)
{
	for (IT it = begin; it != end; it = ++begin)
		while (++it != end)
			*out++ = std::make_pair(*begin, *it);
}


template <class Out, class C>
auto all_pairs_out(Out out, C &&c)
  -> decltype(all_pairs_out(out, c.begin(), c.end()))
{ return      all_pairs_out(out, c.begin(), c.end()); }


