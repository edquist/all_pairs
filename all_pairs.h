#pragma once

#include <utility>

// namespace ltd { }


template <class P, class IT>   // P ~ std::pair<IT, IT>, w/o refs
P next_pair(P prev_pair, IT &&end)
{
	if (++prev_pair.second == end) {
		prev_pair.second = ++prev_pair.first;
		++prev_pair.second;
		if (prev_pair.second == end)  // not needed for sentinal version
			prev_pair.first = end;
	}
	return prev_pair;
}

template <class P, class E2>
P &advance_pair(P &prev_pair, E2 &&e2)
{
	return next_pair<P &, E2>(prev_pair, e2);
}

template <class IT>
struct all_pairs_t {
	IT _begin;
	IT _end;

	struct end_iterator {};  // end sentinal

	struct iterator {
		std::pair<IT, IT> pos;
		IT end;

		typedef decltype(*end) item_type;
		typedef std::pair<item_type, item_type> value_type;

		//value_type &operator*()
		//{ return {*pos.first, *pos.second}; }

		value_type  operator*() const
		{ return {*pos.first, *pos.second}; }

		iterator &operator++() { 
			advance_pair(pos, end);
			return *this;
		}

		bool operator==(const iterator &o) const
		{ return pos == o.pos; }

		bool operator!=(const iterator &o) const
		{ return pos != o.pos; }


		// end sentinal version
		bool operator!=(const end_iterator &) const
		{ return pos.first != end; }
	};

	iterator begin() const {
		IT b2 = _begin;
		return { {_begin, ++b2}, _end };
	}

	iterator     end()   const { return { {_end, _end}, _end }; }
	end_iterator end2()  const { return {}; }  // c++17
};

template <class IT>
all_pairs_t<IT>
all_pairs(IT begin, IT end)
{ return {begin, end}; }

template <class C>
auto all_pairs(C &&c)
   -> decltype(all_pairs(c.begin(), c.end()))
{
	return all_pairs(c.begin(), c.end());
}

