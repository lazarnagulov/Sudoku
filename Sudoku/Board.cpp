/// File: Board.cpp
/// 
/// Definitions of Board class.
/// 
///	Author: Lazar Nagulov 
/// Last modified: 19.12.2023.

#include <unordered_set>
#include <bitset>
#include <random>

#include "Board.h"

Board::Board() {
	memset(board, 0, sizeof(board));
}
Board::~Board() {}

/// <summary>
/// Checks if current board is valid.
/// </summary>
/// <returns>
///		true if current board is valid
/// </returns>
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

	for (int block = 0; block < BOARD_SIZE; ++block) {
		subMatrixSet.clear();
		for (int i = block / BLOCK_SIZE * BLOCK_SIZE; i < block / BLOCK_SIZE * BLOCK_SIZE + BLOCK_SIZE; ++i) {
			for (int j = block % BLOCK_SIZE * BLOCK_SIZE; j < block % BLOCK_SIZE * BLOCK_SIZE + BLOCK_SIZE; ++j) {
				int current = At(i, j);
				if (current != EMPTY && !subMatrixSet.insert(current).second) {
					std::cerr << "Error: Duplicate number " << At(i,j) << " in block "  << block  << " at [" << i << ',' << j << "]"<< std::endl;
					return false;
				}
			}
		}
	}

	return true;
}

constexpr int Board::GetBlock(int row, int col) {
	return (row / Board::BLOCK_SIZE) * Board::BLOCK_SIZE + col / Board::BLOCK_SIZE;
}

bool Board::Backtrack(BitArray& rowSet, BitArray& colSet, BitArray& blockSet) {
	int row, col;
	if (!FindEmpty(row, col)) {
		return true;
	}
	int block = GetBlock(row, col);
	std::bitset<BOARD_SIZE> contains = rowSet[row] | colSet[col] | blockSet[block];
	if (contains.all()) {
		return false;
	}

	for (int number = 1; number <= BOARD_SIZE; ++number) {
		int idx = number - 1;
		if (!contains[idx]) {
			At(row, col) = number;
			rowSet[row].set(idx);
			colSet[col].set(idx);
			blockSet[block].set(idx);
			if (Backtrack(rowSet, colSet, blockSet)) {
				return true;
			}
			rowSet[row].reset(idx);
			colSet[col].reset(idx);
			blockSet[block].reset(idx);
		}
	}
	At(row, col) = 0;
	return false;
}


/// <summary>
///		Checks for errors in current board, prints them and counts them.
/// </summary>
/// <returns>
///		Number of errors.
/// </returns>
int Board::CountErrors(const Board& checking) const {
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
			int originalRow = checking(i, j);
			int originalCol = checking(j, i);
			if (originalRow != EMPTY && currentRow != originalRow) {
				std::cout << "Wrong: Value changed from original " << originalRow << "->" << currentRow << " at [" << i << ',' << j << "]" << std::endl;
			}
			if (originalCol != EMPTY && currentCol != originalCol) {
				std::cout << "Wrong: Value changed from original " << originalCol << "->" << currentCol << " at [" << j << ',' << i << "]" << std::endl;
			}
			if (currentRow != EMPTY && !rowSet.insert(currentRow).second) {
				std::cout << "Wrong: Duplicate number (row " << i << ") " << checking(i, j) << " at [" << i << ',' << j << "]" << std::endl;
				++result;
			}
			if (currentCol != EMPTY && !colSet.insert(currentCol).second) {
				std::cout << "Wrong: Duplicate number (column " << i << ") " << checking(j, i) << " at [" << j << ',' << i << "]" << std::endl;
				++result;
			}
			rowSet.insert(currentRow);
			colSet.insert(currentCol);
		}
	}

	for (int block = 0; block < BOARD_SIZE; ++block) {
		subMatrixSet.clear();
		for (int i = block / BLOCK_SIZE * BLOCK_SIZE; i < block / BLOCK_SIZE * BLOCK_SIZE + BLOCK_SIZE; ++i) {
			for (int j = block % BLOCK_SIZE * BLOCK_SIZE; j < block % BLOCK_SIZE * BLOCK_SIZE + BLOCK_SIZE; ++j) {
				int current = checking(i, j);
				if (current != EMPTY && !subMatrixSet.insert(current).second) {
					std::cout << "Wrong: Duplicate number " << checking(i, j) << " in block " << block << " at [" << i << ',' << j << "]" << std::endl;
					++result;
				}
			}
		}
	}


	return result;
}

/// <summary>
/// Checks if it is possible to put number 'number' in position ('row', 'col') in board.
/// </summary>
/// <param name="row">row index</param>
/// <param name="col">column index</param>
/// <param name="number">digit</param>
/// <returns>true if it is possible to out number in ('row', 'col')</returns>
bool Board::IsPossibleMove(int row, int col, int number) const {
	for (int i = 0; i < Board::BOARD_SIZE; ++i) {
		if (At(i, col) == number) {
			return false;
		}
		if(At(row, i) == number) {
			return false;
		}
	}
	int row0 = (row / BLOCK_SIZE) * BLOCK_SIZE;
	int col0 = (col / BLOCK_SIZE) * BLOCK_SIZE;

	for (int i = 0; i < BLOCK_SIZE; ++i) {
		for (int j = 0; j < BLOCK_SIZE; ++j) {
			if(At(row0 + i, col0 + j) == number){
				return false;
			}
		}
	}
	return true;
}

/// <summary>
/// Generates diagonal in empty board.
/// </summary>
void Board::GenerateDiagonal() {
	for (int i = 0; i < BOARD_SIZE; i += BLOCK_SIZE) {
		FillBlock(i, i);
	}
}

/// <summary>
/// Fills block with random generated values.
/// </summary>
/// <param name="row"> Block row (left corner of block) </param>
/// <param name="col"> Block column (left corner of block) </param>
void Board::FillBlock(int row, int col) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> random(1, BOARD_SIZE);

	std::bitset<BOARD_SIZE> blockSet;
	int number = 0;
	int idx = 0;
	for (int i = 0; i < BLOCK_SIZE; ++i) {
		for (int j = 0; j < BLOCK_SIZE; ++j) {
			do {
				number = random(rng);
				idx = number - 1;
			} while (blockSet.test(idx));
			At(row + i, col + j) = number;
			blockSet.set(idx);
		}
	}
}

/// <summary>
/// Generates non diagonal elements in board.
/// </summary>
/// <param name="row">Starting row (most likely 0)</param>
/// <param name="col">Starting column (most likely 0)</param>
/// <returns></returns>
bool Board::GenerateOther(int row, int col) {
	// Last column?
	if (col >= Board::BOARD_SIZE && row < Board::BOARD_SIZE - 1) {
		row += 1;
		col = 0;
	}

	// End?
	if (row >= Board::BOARD_SIZE && col >= Board::BOARD_SIZE) {
		return true;
	}

	// Generate blocks first.
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

	// Solve board with backtracking.
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


/// <summary>
/// Removes 'count' digits randomly from board.
/// </summary>
/// <param name="count">Number of digit to remove</param>
void Board::RemoveNumber(int count) {
	while (count) {
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> random(0, BOARD_SIZE * BOARD_SIZE - 1);

		int block = random(rng);
		int row = block / BOARD_SIZE;
		int col = block % BOARD_SIZE;
		if (At(row, col) != 0) {
			--count;
			At(row, col) = 0;
		}
	}
}

/// <summary>
/// Finds first empty place in board, staring with position ('row', 'col').
/// </summary>
/// <param name="row">String row</param>
/// <param name="col">Staritng column</param>
/// <returns></returns>
bool Board::FindEmpty(int& row, int& col) {
	for (row = 0; row < Board::BOARD_SIZE; ++row)
		for (col = 0; col < Board::BOARD_SIZE; ++col)
			if (At(row, col) == Board::EMPTY)
				return true;
	return false;
}

/// <summary>
/// Sets all elements in board to 0.
/// </summary>
void Board::Clear() {
	memset(board, 0, sizeof(board));
}

/// <summary>
/// Get reference of board element. Does bound checking.
/// </summary>
/// <param name="row"></param>
/// <param name="col"></param>
/// <returns>Reference to element in board</returns>
int& Board::At(int row, int col) {
	if (row >= BOARD_SIZE || row < 0 || col >= BOARD_SIZE || col < 0)
		throw std::out_of_range("Error: Index out of range in board");
	return board[row * BOARD_SIZE + col];
}

/// <summary>
/// Get reference of board element. Does bound checking.
/// </summary>
/// <param name="row"></param>
/// <param name="col"></param>
/// <returns>Reference to element in board</returns>
const int& Board::At(int row, int col) const {
	if (row >= BOARD_SIZE || row < 0 || col >= BOARD_SIZE || col < 0)
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
			char field;
			in >> field;
			if (field == Board::EMPTY_CHAR) {
				board(i, j) = 0;
			}
			else {
				board(i, j) = field - '0';
			}
		}
	}

	return in;
}

std::ofstream& operator<<(std::ofstream& out, const Board& board) {
	for (int i = 0; i < Board::BOARD_SIZE; ++i) {
		for (int j = 0; j < Board::BOARD_SIZE; ++j) {
			if (board(i, j) == Board::EMPTY) {
				out << Board::EMPTY_CHAR << ' ';
			}
			else {
				out << board(i, j) << ' ';
			}
		}
		out << "\n";
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, const Board& board) {
	for (int i = 0; i < Board::BOARD_SIZE; ++i) {
		for (int j = 0; j < Board::BOARD_SIZE; ++j) {
			if (board(i, j) == Board::EMPTY) {
				out << Board::EMPTY_CHAR << ' ';
			}
			else {
				out << board(i, j) << " ";
			}

			if ((j + 1) % Board::BLOCK_SIZE == 0 && j < Board::BOARD_SIZE - 1) {
				out << "| ";
			}
		}
		out << "\n";
		if ((i + 1) % Board::BLOCK_SIZE == 0 && i < Board::BOARD_SIZE - 1) {
			out << "------+-------+------\n";
		}
	}
	return out;
}
