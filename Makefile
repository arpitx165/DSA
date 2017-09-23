all:
	$(CXX) -pthread -std=c++11 -Wall -Wextra graph.cpp -o graph

test:
	 ./graph || exit 1
