CXX = g++
CXXFLAGS = -O3 -Wall -std=c++11

demo: demo.cpp all_pairs.h
	$(LINK.cpp) $< $(LDLIBS) -o $@

clean:
	$(RM) demo
