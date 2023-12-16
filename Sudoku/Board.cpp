#include "Board.h"

Board::Board() {
	memset(board, 0, sizeof(board));
}
Board::~Board() {}

bool Board::IsValid() {
	return false;
}
int Board::Get(int row, int col) {
	if (row >= 9 || row < 0 || col >= 9 || col < 0)
		throw std::out_of_range("Index out of range in board");
	return board[row * BOARD_SIZE + col];
}

int Board::operator ()(int row, int col) {
	return board[row * BOARD_SIZE + col];
}

std::istream& operator>>(std::istream& in, Board& board) {
	return in;
}
std::ostream& operator<<(std::ostream& out, const Board& board) {
	return out;
}