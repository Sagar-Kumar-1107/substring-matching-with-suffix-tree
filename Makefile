
CXX = g++
CXXFLAGS = -Wall -g


all: string_generator extend_part


string_generator: string_generator.cpp
	$(CXX) $(CXXFLAGS) string_generator.cpp -o string_generator


extend_part: extend_part.cpp
	$(CXX) $(CXXFLAGS) extend_part.cpp -o extend_part


run: all
	@echo "--- 1. Generating Data ---"
	./string_generator
	@echo "--- 2. Running Solver ---"
	./extend_part

clean:
	rm -f string_generator extend_part input.txt