#include <unordered_set>
#include <bitset>

#include "Board.h"

Board::Board() {
	memset(board, 0, sizeof(board));
}
Board::~Board() {}

bool Board::IsValid() const {
	std::unordered_set<int> rowSet;
	std::unordered_set<int> colSet;
	std::unordered_set<int> subMatrixSet;

	for (int i = 0; i < BOARD_SIZE; ++i) {
		rowSet.clear();
		colSet.clear();
		for (int j = 0; j < BOARD_SIZE; ++j) {
			int currentRow = At(i, j);
			int currentCol = At(j, i);
			if (currentRow != EMPTY && !rowSet.insert(currentRow).second) {
				std::cerr << "Error: Duplicate number " << At(i, j) << " in row " << i << " at [" << i << ',' << j << "]" << std::endl;
				return false;
			}
			if (currentCol != EMPTY && !colSet.insert(currentCol).second) {
				std::cerr << "Error: Duplicate number " << At(j,i) << " in colomn " << i << " at [" << j << ',' << i << "]" << std::endl;
				return false;
			}
			rowSet.insert(currentRow);
			colSet.insert(currentCol);
		}
	}

	for (int block = 0; block < 9; ++block) {
		subMatrixSet.clear();
		for (int i = block / 3 * 3; i < block / 3 * 3 + 3; ++i) {
			for (int j = block % 3 * 3; j < block % 3 * 3 + 3; ++j) {
				int current = At(i, j);
				if (current != EMPTY && !subMatrixSet.insert(current).second) {
					std::cerr << "Wrong: Duplicate number " << At(i,j) << " in block "  << block  << " at [" << i << ',' << j << "]"<< std::endl;
					return false;
				}
			}
		}
	}

	return true;

}

int Board::CountErrors() const {
	int result = 0;
	std::unordered_set<int> rowSet;
	std::unordered_set<int> colSet;
	std::unordered_set<int> subMatrixSet;

	for (int i = 0; i < BOARD_SIZE; ++i) {
		rowSet.clear();
		colSet.clear();
		for (int j = 0; j < BOARD_SIZE; ++j) {
			int currentRow = At(i, j);
			int currentCol = At(j, i);
			if (currentRow != EMPTY && !rowSet.insert(currentRow).second) {
				std::cout << "Wrong: Duplicate number " << At(i, j) << " in row " << i << " at [" << i << ',' << j << "]" << std::endl;
				++result;
			}
			if (currentCol != EMPTY && !colSet.insert(currentCol).second) {
				std::cout << "Wrong: Duplicate number " << At(j, i) << " in colomn " << i << " at [" << j << ',' << i << "]" << std::endl;
				++result;
			}
			rowSet.insert(currentRow);
			colSet.insert(currentCol);
		}
	}

	for (int block = 0; block < 9; ++block) {
		subMatrixSet.clear();
		for (int i = block / 3 * 3; i < block / 3 * 3 + 3; ++i) {
			for (int j = block % 3 * 3; j < block % 3 * 3 + 3; ++j) {
				int current = At(i, j);
				if (current != EMPTY && !subMatrixSet.insert(current).second) {
					std::cout << "Error: Duplicate number " << At(i, j) << " in block " << block << " at [" << i << ',' << j << "]" << std::endl;
					++result;
				}
			}
		}
	}

	return result;
}


bool Board::IsPossibleMove(int row, int col, int number) const {
	for (int i = 0; i < Board::BOARD_SIZE; ++i) {
		if (At(i, col) == number) {
			return false;
		}
		if(At(row, i) == number) {
			return false;
		}
	}
	int row0 = (row / 3) * 3;
	int col0 = (col / 3) * 3;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if(At(row0 + i, col0 + j) == number){
				return false;
			}
		}
	}
	return true;
}

void Board::GenerateDiagonal() {
	for (int i = 0; i < BOARD_SIZE; i += 3) {
		FillBlock(i, i);
	}
}

void Board::FillBlock(int row, int col) {
	std::bitset<BOARD_SIZE> blockSet;
	int number = 0;
	int idx = 0;
	for (int i = 0; i < BLOCK_SIZE; ++i) {
		for (int j = 0; j < BLOCK_SIZE; ++j) {
			do {
				number = (std::rand() % 9) + 1;
				idx = number - 1;
			} while (blockSet.test(idx));
			At(row + i, col + j) = number;
			blockSet.set(idx);
		}
	}
}

bool Board::GenerateOther(int row, int col) {
	if (col >= Board::BOARD_SIZE && row < Board::BOARD_SIZE - 1) {
		row += 1;
		col = 0;
	}

	if (row >= Board::BOARD_SIZE && col >= Board::BOARD_SIZE) {
		return true;
	}

	if (row < BLOCK_SIZE) {
		if (col < BLOCK_SIZE) {
			col = BLOCK_SIZE;
		}
	}
	else if (row < Board::BOARD_SIZE - BLOCK_SIZE) {
		if (col == (int)(row / BLOCK_SIZE) * BLOCK_SIZE) {
			col += BLOCK_SIZE;
		}
	}
	else if (col == Board::BOARD_SIZE - BLOCK_SIZE) {
		row += 1;
		col = 0;
		if (row >= Board::BOARD_SIZE) {
			return true;
		}
	}
	for (int number = 1; number <= Board::BOARD_SIZE; ++number) {
		if (IsPossibleMove(row, col, number)) {
			At(row, col) = number;
			if (GenerateOther(row, col + 1)) {
				return true;
			}
			At(row, col) = 0;
		}
	}
	return false;
}

void Board::RemoveDigit(int count) {
	while (count) {
		int block = (int)floor((float)(rand() / double(RAND_MAX) * BOARD_SIZE  * BOARD_SIZE + 1)) - 1;
		int row = block / BOARD_SIZE;
		int col = block % BOARD_SIZE;
		if (At(row, col) != 0) {
			--count;
			At(row, col) = 0;
		}
	}
}

bool Board::FindEmpty(int& row, int& col) {
	for (row = 0; row < Board::BOARD_SIZE; ++row)
		for (col = 0; col < Board::BOARD_SIZE; ++col)
			if (At(row, col) == Board::EMPTY)
				return true;
	return false;
}

void Board::Clear() {
	memset(board, 0, sizeof(board));
}

int& Board::At(int row, int col) {
	if (row >= 9 || row < 0 || col >= 9 || col < 0)
		throw std::out_of_range("Error: Index out of range in board");
	return board[row * BOARD_SIZE + col];
}

const int& Board::At(int row, int col) const {
	if (row >= 9 || row < 0 || col >= 9 || col < 0)
		throw std::out_of_range("Error: Index out of range in board");
	return board[row * BOARD_SIZE + col];
}

const int& Board::operator()(int row, int col) const {
	return board[row * BOARD_SIZE + col];
}

int& Board::operator()(int row, int col) {
	return board[row * BOARD_SIZE + col];
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
			out << board(i, j) << ' ';
		}
		out << "\n";
	}
	return out;
}
