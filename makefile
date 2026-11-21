CXXFLAGS := -Wall -Wextra -Wpedantic -Werror -g

all: main

main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o

main.cpp:
	echo "#include <iostream>" >> main.cpp
	echo "int main() {" >> main.cpp
	echo "std::ios::sync_with_stdio(false);" >> main.cpp
	echo "std::cin.tie(nullptr);" >> main.cpp
	echo "}" >> main.cpp

clean:
	rm -f main main.o
