#pragma once
#include <iostream>

class Board {
public:
	static const int BOARD_SIZE = 9;

	Board();
	~Board();

	bool IsValid() const;

	int& operator()(int row, int col);
	const int operator()(int row, int col) const;
	int Get(int row, int col) const;

	friend std::istream& operator>>(std::istream& in, Board& board);
	friend std::ostream& operator<<(std::ostream& out, const Board& board);
private:
	int board[BOARD_SIZE * BOARD_SIZE];
};