CXX = clang++
A_CXXFLAGS = -std=c++23 -O2 -Wall -fsanitize=address,undefined -g
B_CXXFLAGS = -std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wshadow \
	-fsanitize=address,undefined -fno-omit-frame-pointer

all: a b

a: a.cpp
	$(CXX) $(A_CXXFLAGS) $< -o $@

b: b.cpp
	$(CXX) $(B_CXXFLAGS) $< -o $@

clean:
	rm -f a b

.PHONY: all clean
