/// File: Sudoku.h
/// 
/// Declarations of Sudoku class.   
/// Contains a main game functions such as Run, Solve, Generate.
/// 
///	Author: Lazar Nagulov 
/// Last modified: 18.12.2023.
#pragma once
#include <fstream>
#include <bitset>

#include "Board.h"

class Sudoku {
public:
	enum Difficulty {
		EASY = 43,
		MEDIUM = 50,
		HARD = 56,
		VERY_HARD = 60,
	};

	Sudoku(std::string& inputFile, std::string& outputFile);
	~Sudoku();

	void Run();
	void Solve();
	void CheckSolution(std::ifstream& in);
	void Generate(Difficulty difficulty);


	friend std::ostream& operator<<(std::ostream& out, const Sudoku& sudoku);
private:
	void SolvingOptions();
	std::string inputFile, outputFile;
	int emptyCount;
	int currentRound;
	int correctCount;
	int wrongCount;
	Board board;
};
