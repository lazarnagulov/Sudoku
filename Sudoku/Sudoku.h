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
		VERY_EASY = 17,
		EASY = 35,
		MEDIUM = 46,
		HARD = 50,
		VERY_HARD = 59,
	};

	Sudoku();
	Sudoku(Board& board);
	Sudoku(std::ifstream& in);
	~Sudoku();

	static void Run();
	void Solve();
	void Generate(Difficulty difficulty);

	friend std::ostream& operator<<(std::ostream& out, const Sudoku& sudoku);
	friend std::istream& operator>>(std::istream& in, Sudoku& sudoku);
private:
	int currentRound;
	int correctCount;
	int wrongCount;
	Board board;
};
