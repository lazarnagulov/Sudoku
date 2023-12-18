/// File: Sudoku.cpp
/// 
/// Definitions of Sudoku class.
/// 
///	Author: Lazar Nagulov 
/// Last modified: 27.12.2023.

#include <array>
#include <bitset>
#include <cstdlib>

#include "Sudoku.h"

Sudoku::Sudoku() : correctCount(0), wrongCount(0), currentRound(1) {}
Sudoku::Sudoku(Board& board) : correctCount(0), wrongCount(0), currentRound(1), board(board) {}
Sudoku::Sudoku(std::ifstream& in) : correctCount(0), wrongCount(0), currentRound(1) {
	in >> board;
}
Sudoku::~Sudoku() {}

void Sudoku::Run() {
    std::cout << std::endl;
	std::cout << "Welcome to \"Sudokusphere\" Sudoku Solver!" << std::endl;
	std::cout << "1 > Generate new Sudoku puzzle" << std::endl;
	std::cout << "2 > Load Sudoku puzzle from file" << std::endl;
	std::cout << "3 > Exit" << std::endl;

    int ans;
    std::cout << ">> ";
    std::cin >> ans;
    if (ans == 1) {
        Generate(Difficulty::HARD);
        std::cout << "Sudoku puzzle is generated!" << std::endl;
        std::cout << *this << std::endl;
        SolvingOptions();
    }
    else if (ans == 2) {
        std::cerr << "Not implemented" << std::endl;
    }
    else if (ans == 3) {
        exit(0);
    }
    else {
        std::cerr << "Invalid command" << std::endl;
        return;
    }
}

void Sudoku::SolvingOptions() {
    std::cout << "1 > Import solution" << std::endl;
    std::cout << "2 > Solve" << std::endl;

    int ans;
    std::cout << ">> ";
    std::cin >> ans;
    if (ans == 1) {
        std::cerr << "Not implemented" << std::endl;
    }
    else if (ans == 2) {
        Solve();
        std::cout << *this << std::endl;
    }
    else {
        std::cerr << "Invalid command" << std::endl;
    }
    ++currentRound;
}

constexpr int GetBlock(int row, int col) {
    return (row / Board::BLOCK_SIZE) * Board::BLOCK_SIZE + col / Board::BLOCK_SIZE;
}

static bool BacktrackSolver(Board& board) {
    int row, col;
    if (!board.FindEmpty(row, col)) {
        return true;
    }
    for (int number = 1; number <= Board::BOARD_SIZE; ++number) {
        if (board.IsPossibleMove(row, col, number)) {
            board(row, col) = number;
            if (BacktrackSolver(board)) {
                return true;
            }
            board(row, col) = Board::EMPTY;
        }
    }
    return false;
}

using BitArray = std::array<std::bitset<Board::BOARD_SIZE>, Board::BOARD_SIZE>;

static bool Backtrack(Board& board, BitArray& rowSet, BitArray& colSet, BitArray& blockSet) {
    int row, col;
    if (!board.FindEmpty( row, col)) {
        return true;
    }
    int block = GetBlock(row, col);
    std::bitset<Board::BOARD_SIZE> contains = rowSet[row] | colSet[col] | blockSet[block];
    if (contains.all()) {
        return false;
    }

    for (int number = 1; number <= Board::BOARD_SIZE; ++number) {
        int idx = number - 1;
        if (!contains[idx]) {
            board(row, col) = number;
            rowSet[row].set(idx);
            colSet[col].set(idx);
            blockSet[block].set(idx);
            if (Backtrack(board, rowSet, colSet, blockSet)) {
                return true;
            }
            rowSet[row].reset(idx);
            colSet[col].reset(idx);
            blockSet[block].reset(idx);
        }
    }
    board(row, col) = 0;
    return false;
}



void Sudoku::Solve() {
    BitArray rowSet;
    BitArray colSet;
    BitArray blockSet;

    for (int row = 0; row < Board::BOARD_SIZE; ++row) {
        for (int col = 0; col < Board::BOARD_SIZE; ++col) {
            int number = board(row, col);
            if (number != Board::EMPTY) {
                int idx = number - 1;
                rowSet[row].set(idx);
                colSet[col].set(idx);
                int blockIdx = GetBlock(row, col);
                blockSet[blockIdx].set(idx);
            }
        }
    }

    Backtrack(board, rowSet, colSet, blockSet);
}

void Sudoku::Generate(Difficulty difficulty) {
    board.Clear();
    board.GenerateDiagonal();
    board.GenerateOther(0,0);
    board.RemoveDigit(difficulty);
}


std::ostream& operator<<(std::ostream& out, const Sudoku& sudoku) {
    out << "Round: " << sudoku.currentRound << '\n';
    out << "Correct: " << sudoku.correctCount << '\n';
    out << "Wrong: " << sudoku.wrongCount << '\n';
    out << sudoku.board;
	return out;
}

std::istream& operator>>(std::istream& in, Sudoku& sudoku) {
    in >> sudoku.board;
    return in;
}
