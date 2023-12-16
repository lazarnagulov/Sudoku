#pragma once
#include <iostream>

class Board {
public:
	static const int BOARD_SIZE = 9;
	static const int EMPTY = 0;
	static const char EMPTY_CHAR = '_';

	Board();
	~Board();

	bool IsValid() const;

	const int& operator()(int row, int col) const;
	int& operator()(int row, int col);
	int Get(int row, int col) const;
	bool IsPossibleMove(int row, int col, int number) const;
	
	friend std::istream& operator>>(std::istream& in, Board& board);
	friend std::ostream& operator<<(std::ostream& out, const Board& board);
private:
	int board[BOARD_SIZE * BOARD_SIZE];
};