CXX = g++
CXXFLAGS = -O3 -Wall -std=c++11

demo: demo.cpp all_pairs.h all_pairs_out.h generic_ostream_iterator.h
	$(LINK.cpp) $< $(LDLIBS) -o $@

clean:
	$(RM) demo
