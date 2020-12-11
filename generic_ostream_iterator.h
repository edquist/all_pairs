#pragma once

//#include <iterator>

template <class OS, class D>
struct generic_ostream_iterator
{
	//typedef std::output_iterator_tag iterator_category;
	//typedef void value_type;

	OS &os;
	D  delim;

	template <class T>
	generic_ostream_iterator &operator= (T &&x) {
		os << x;
		if (delim)
			os << delim;
		return *this;
	}

	generic_ostream_iterator &operator*()     { return *this; }
	generic_ostream_iterator &operator++()    { return *this; }
	generic_ostream_iterator &operator++(int) { return *this; }
};

template <class OS, class D>
generic_ostream_iterator<OS, D>
ostreamer(OS &os, D delim) { return {os, delim}; }

template <class OS>
generic_ostream_iterator<OS, char>
ostreamer(OS &os) { return {os, '\n'}; }

