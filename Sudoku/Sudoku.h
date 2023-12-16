#pragma once
#include "Board.h"

class Sudoku {
public:
	Sudoku();
	~Sudoku();

	void Solve();
	void Generate();
	void Reset();
private:
	bool IsPossibleMove(int row, int col, int number);
private:
	Board board;
};