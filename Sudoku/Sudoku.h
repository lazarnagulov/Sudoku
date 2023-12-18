/// File: Sudoku.h
/// 
/// Declarations of Sudoku class.   
/// 
///	Author: Lazar Nagulov 
/// Last modified: 27.12.2023.
#pragma once
#include <fstream>

#include "Board.h"

class Sudoku {
public:
	enum Difficulty {
		EASY = 40,
		MEDIUM = 50,
		HARD = 56,
		VERY_HARD = 64,
	};

	Sudoku();
	Sudoku(Board& board);
	Sudoku(std::ifstream& in);
	~Sudoku();

	void Run();
	void Solve();
	void Generate(Difficulty difficulty);

	friend std::ostream& operator<<(std::ostream& out, const Sudoku& sudoku);
	friend std::istream& operator>>(std::istream& in, Sudoku& sudoku);
private:
	void SolvingOptions();

	std::ifstream inputFile;
	std::ofstream outputFile;
	int currentRound;
	int correctCount;
	int wrongCount;
	Board board;
};
