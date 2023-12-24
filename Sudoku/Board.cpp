/// Board.cpp
/// 
/// Definitions of Board class.
/// 
///	Author: Lazar Nagulov 
/// Last modified: 23rd December 2023

#include <unordered_set>
#include <array>
#include <bitset>
#include <random>

#include "Board.h"

Board::Board() {
	memset(board, 0, sizeof(board));
}
Board::~Board() {}

bool Board::IsValid() const {
	std::unordered_set<int> rowSet;
	std::unordered_set<int> colSet;
	std::unordered_set<int> blockSet;

	/// Check rows.
	for (int row = 0; row < BOARD_SIZE; ++row) {
		rowSet.clear();
		for (int col = 0; col < BOARD_SIZE; ++col) {
			int currentRow = At(row, col);

			if (currentRow != EMPTY && !rowSet.insert(currentRow).second) {
				std::cerr << "Error: Duplicate number " << At(row, col) << " in row " << row << " at " << col << "." << std::endl;
				return false;
			}
		}
	}

	// Check columns.
	for (int col = 0; col < BOARD_SIZE; ++col) {
		colSet.clear();
		for (int row = 0; row < BOARD_SIZE; ++row) {
			int currentCol = At(row, col);

			if (currentCol != EMPTY && !colSet.insert(currentCol).second) {
				std::cerr << "Error: Duplicate number " << At(row, col) << " in column " << col << " at " << row << "." << std::endl;
				return false;
			}
		}
	}

	// Check blocks (submatrices).
	for (int block = 0; block < BOARD_SIZE; ++block) {
		blockSet.clear();
		for (int i = block / BLOCK_SIZE * BLOCK_SIZE; i < block / BLOCK_SIZE * BLOCK_SIZE + BLOCK_SIZE; ++i) {
			for (int j = block % BLOCK_SIZE * BLOCK_SIZE; j < block % BLOCK_SIZE * BLOCK_SIZE + BLOCK_SIZE; ++j) {
				int current = At(i, j);

				if (current != EMPTY && !blockSet.insert(current).second) {
					std::cerr << "Error: Duplicate number " << At(i, j) << " in block " << block << " at (" << i << ',' << j << ")." << std::endl;
					return false;
				}
			}
		}
	}

	return true;
}

inline int Board::GetBlock(int row, int col) {
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


bool Board::IsDuplicate(int row, int col, PairArray& buff) {
	int& current = At(row, col);
	int idx = current - 1;

	if (current == EMPTY)
		return false;

	if (buff[idx].first == -1) {
		buff[idx] = std::make_pair(row, col);
		return false;
	}
	else {
		return true;
	}
}

int Board::CountErrors(const Board& original) {
	int result = 0;

	PairArray buff;

	for (int row = 0; row < BOARD_SIZE; ++row) {
		std::fill(buff.begin(), buff.end(), std::make_pair(-1, -1));
		for (int col = 0; col < BOARD_SIZE; ++col) {
			int& current = At(row, col);
			int currentOriginal = original(row, col);
			int idx = current - 1;
			if (currentOriginal != EMPTY && currentOriginal != current) {
				std::cout << "Wrong: Value changed from original at (" << row  << ',' << col << ")." << std::endl;
				++result;
				At(row, col) = original(row, col);
				continue;
			}
			if (IsDuplicate(row, col, buff)) {
				std::cout << "Wrong: Duplicate number " << At(row, col) << " in row " << row << " at " << col << "." << std::endl;
				++result;
				if (currentOriginal == current) {
					At(buff[idx].first, buff[idx].second) = 0;
				}
				else {
					current = 0;
				}
			}
		}
	}

	for (int col = 0; col < BOARD_SIZE; ++col) {
		std::fill(buff.begin(), buff.end(), std::make_pair(-1, -1));
		for (int row = 0; row < BOARD_SIZE; ++row) {
			int& current = At(row, col);
			int idx = current - 1;
			if (IsDuplicate(row, col, buff)) {
				std::cout << "Wrong: Duplicate number " << At(row, col) << " in column " << col << " at " << row << "." << std::endl;
				++result;
				if (original(row, col) == current) {
					At(buff[idx].first, buff[idx].second) = 0;
				}
				else {
					current = 0;
				}
			}
		}
	}

	for (int block = 0; block < BOARD_SIZE; ++block) {
		std::fill(buff.begin(), buff.end(), std::make_pair(-1, -1));
		for (int row = block / BLOCK_SIZE * BLOCK_SIZE; row < block / BLOCK_SIZE * BLOCK_SIZE + BLOCK_SIZE; ++row) {
			for (int col = block % BLOCK_SIZE * BLOCK_SIZE; col < block % BLOCK_SIZE * BLOCK_SIZE + BLOCK_SIZE; ++col) {
				int& current = At(row, col);
				int idx = current - 1;
				if (IsDuplicate(row, col, buff)) {
					std::cerr << "Error: Duplicate number " << At(row, col) << " in block " << block << " at (" << row << ',' << col << ")" << std::endl;
					++result;
					if (original(row, col) == current) {
						At(buff[idx].first, buff[idx].second) = 0;
					}
					else {
						current = 0;
					}
				}

			}
		}
	}


	return result;
}
int Board::CountEmpty() {
	int result = 0;
	for (int row = 0; row < Board::BOARD_SIZE; ++row) {
		for (int col = 0; col < Board::BOARD_SIZE; ++col) {
			if (At(row, col) == EMPTY) {
				++result;
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

void Board::GenerateDiagonal() {
	for (int i = 0; i < BOARD_SIZE; i += BLOCK_SIZE) {
		FillBlock(i, i);
	}
}

void Board::FillBlock(int row, int col) {
	// Generate random number from 1 to BOAD_SIZE.
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

void Board::RemoveNumber(int count) {
	while (count) {
		// Generate random number from 0 to BOAD_SIZE^2 - 1.
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
	if (row >= BOARD_SIZE || row < 0 || col >= BOARD_SIZE || col < 0)
		throw std::out_of_range("Error: Index out of range in board");
	return board[row * BOARD_SIZE + col];
}

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

/// <summary>
/// Reads the contents of a Sudoku board from the input stream and updates the provided Board object.
/// Expects characters representing the Sudoku grid, with '0' for empty cells.
/// </summary>
/// <param name="in">Reference to the input stream.</param>
/// <param name="board">Reference to the Board object to be updated.</param>
/// <returns>Reference to the input stream after reading the board.</returns>
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

/// <summary>
/// Writes the contents of a board to the output file stream.
/// Empty cells are represented by the designated empty character.
/// </summary>
/// <param name="out">Reference to the output file stream.</param>
/// <param name="board">Reference to the const Board object to be written.</param>
/// <returns>Reference to the output file stream after writing the board.</returns>
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

/// <summary>
/// Writes the formatted contents of a board to the output stream.
/// Empty cells are represented by the designated empty character.
/// The output includes horizontal and vertical separators to create a visual representation of the grid.
/// </summary>
/// <param name="out">Reference to the output stream.</param>
/// <param name="board">Reference to the const Board object to be written.</param>
/// <returns>Reference to the output stream after writing the formatted board.</returns>
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
