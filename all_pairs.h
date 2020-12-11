#pragma once

#include <utility>


template <class P, class IT>   // P ~ std::pair<IT, IT>, w/o refs
P next_pair(P pair, IT &&end)
{
	if (++pair.second == end) {
		pair.second = ++pair.first;
		++pair.second;
		if (pair.second == end)  // not needed for sentinal version
			pair.first = end;
	}
	return pair;
}


template <class P, class IT>
P &advance_pair(P &prev_pair, IT &&end)
{
	return next_pair<P &, IT>(prev_pair, std::forward<IT>(end));
}


template <class IT>
struct pairator {
	IT _begin;
	IT _end;

	struct iterator;
	struct end_iterator {};  // end sentinal

	iterator begin() const {
		iterator b { {_begin, _begin}, _end };
		return _begin == _end ? b : ++b;
	}

	iterator     end()   const { return { {_end, _end}, _end }; }
	end_iterator end2()  const { return {}; }  // c++17
};


template <class IT>
struct pairator<IT>::iterator {
	std::pair<IT, IT> pos;
	IT end;

	typedef decltype(*end) item_type;
	typedef std::pair<item_type, item_type> value_type;

	value_type operator*() const { return {*pos.first, *pos.second}; }

	iterator &operator++() {
		advance_pair(pos, end);
		return *this;
	}

	bool operator==(const iterator &o) const { return pos == o.pos; }
	bool operator!=(const iterator &o) const { return pos != o.pos; }

	// end sentinal version
	bool operator!=(end_iterator) const { return pos.first != end; }
};


template <class IT>
pairator<IT>
all_pairs(IT begin, IT end)
{ return {begin, end}; }


template <class C>
auto all_pairs(C &&c)
  -> decltype(all_pairs(c.begin(), c.end()))
{ return      all_pairs(c.begin(), c.end()); }

