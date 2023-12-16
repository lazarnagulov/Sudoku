#include "Board.h"

Board::Board() {
	memset(board, 0, sizeof(board));
}
Board::~Board() {}

bool Board::IsValid() const {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			if (!IsPossibleMove(i, j, board[i * BOARD_SIZE + j])) {
				return false;
			}
		}
	}
	return true;
}

int Board::Get(int row, int col) const {
	if (row >= 9 || row < 0 || col >= 9 || col < 0)
		throw std::out_of_range("Index out of range in board");
	return board[row * BOARD_SIZE + col];
}

const int& Board::operator()(int row, int col) const {
	return board[row * BOARD_SIZE + col];
}

int& Board::operator()(int row, int col) {
	return board[row * BOARD_SIZE + col];
}

bool Board::IsPossibleMove(int row, int col, int number) const {
	for (int i = 0; i < Board::BOARD_SIZE; ++i) {
		if (board[i * BOARD_SIZE + col] == number) {
			return false;
		}
	}
	for (int i = 0; i < Board::BOARD_SIZE; ++i) {
		if (board[row * BOARD_SIZE + i] == number) {
			return false;
		}
	}
	int row0 = (row / 3) * 3;
	int col0 = (col / 3) * 3;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (board[(row0 + i) * BOARD_SIZE + col0 + j] == number) {
				return false;
			}
		}
	}
	return true;
}

std::istream& operator>>(std::istream& in, Board& board) {
	for (int i = 0; i < Board::BOARD_SIZE; ++i) {
		for (int j = 0; j < Board::BOARD_SIZE; ++j) {
			in >> board(i, j);
		}
	}
	return in;
}
std::ostream& operator<<(std::ostream& out, const Board& board) {
	for (int i = 0; i < Board::BOARD_SIZE; ++i) {
		for (int j = 0; j < Board::BOARD_SIZE; ++j) {
			if (board(i, j) == Board::EMPTY) {
				out << Board::EMPTY_CHAR << ' ';
				continue;
			}
			out << board(i, j) << ' ';
		}
		out << '\n';
	}
	return out;
}