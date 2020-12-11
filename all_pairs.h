#pragma once

#include <utility>


template <class P, class End>   // P ~ std::pair<IT, IT>, w/o refs
P next_pair(P pair, End &&end)
{
	if (++pair.second == end)
		if (++(pair.second = ++pair.first) == end)
			pair.first = pair.second;  // not needed for sentinel version
	return pair;
}


template <class P, class End>
P &advance_pair(P &prev_pair, End &&end)
{
	return next_pair<P &, End>(prev_pair, std::forward<End>(end));
}


template <class IT, class End=IT>
struct pairator {
	IT  _begin;
	End _end;

	struct iterator;
	struct end_iterator {};  // end sentinel

	iterator begin() const {
		iterator b { {_begin, _begin}, _end };
		return _begin == _end ? b : ++b;
	}

	iterator     end()   const { return { {_end, _end}, _end }; }
	end_iterator end2()  const { return {}; }  // c++17
};


template <class IT, class End>
struct pairator<IT, End>::iterator {
	std::pair<IT, IT> pos;
	End end;

	typedef decltype(*std::declval<IT>())   item_type;
	typedef std::pair<item_type, item_type> value_type;

	value_type operator*() const { return {*pos.first, *pos.second}; }

	iterator &operator++() {
		advance_pair(pos, end);
		return *this;
	}

	bool operator==(const iterator &o) const { return pos == o.pos; }
	bool operator!=(const iterator &o) const { return pos != o.pos; }

	// end sentinel version
	bool operator!=(end_iterator) const { return pos.second != end; }
};


template <class IT, class End=IT>
pairator<IT, End>
all_pairs(IT begin, End end)
{ return {begin, end}; }


template <class C>
auto all_pairs(C &&c)
  -> decltype(all_pairs(c.begin(), c.end()))
{ return      all_pairs(c.begin(), c.end()); }

