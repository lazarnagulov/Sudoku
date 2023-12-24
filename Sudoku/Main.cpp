#include <iostream>

#include "Test.h"
#include "Sudoku.h"


void Usage() {
	std::cerr << "Usage:" << std::endl;
	std::cerr << "./Sudoku <input.txt> <output.txt>" << std::endl;
	std::cerr << "    input.txt   - Read puzzle from this file" << std::endl;
	std::cerr << "    output.txt  - Write puzzles into this file" << std::endl;
	std::cerr << "./Sudoku -test" << std::endl;
}

int main(int argc, char** argv) {
	if (strcmp(argv[1], "-test") == 0) {
		std::cout << "Testing:" << std::endl;
		TestRun();
		return 0;
	}

	if (argc != 3) {
		Usage();
		return 1;
	}

	std::string input = argv[1];
	std::string output = argv[2];
	Sudoku s(input, output);
	s.Run();
}

