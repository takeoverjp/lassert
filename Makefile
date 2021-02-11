PROGRAMS=test11 test14
all: $(PROGRAMS)

CPPFLAGS=-DTEST_LASSERT
CXXFLAGS=-W -Wall -g -Og
test14: test.cc lassert.h
	g++ -std=c++14 $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

test11: test.cc lassert.h
	g++ -std=c++11 $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

format:
	clang-format -i *.h *.cc

test: $(PROGRAMS)
	./test11
	./test14

clean:
	rm -f $(PROGRAMS) *~

.PHONY: all clean test format
