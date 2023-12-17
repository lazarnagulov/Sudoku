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
	std::cout << "Welcome to Sudoku Solver!" << std::endl;
	std::cout << "1 > Generate new Sudoku table" << std::endl;
	std::cout << "2 > Load Sudoku table from file" << std::endl;
	std::cout << "3 > Exit" << std::endl;
}

constexpr int GetBlock(int row, int col) {
    return (row / 3) * 3 + col / 3;
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

static bool OptimizedBacktrackSolver(Board& board, std::array<std::bitset<9>, 9>& rowSet, std::array<std::bitset<9>, 9>& colSet, std::array<std::bitset<9>, 9>& blockSet) {
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
            if (OptimizedBacktrackSolver(board, rowSet, colSet, blockSet)) {
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
    
    //board.IsValid();
#if 1
    std::array<std::bitset<Board::BOARD_SIZE>, Board::BOARD_SIZE> rowSet = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    std::array<std::bitset<Board::BOARD_SIZE>, Board::BOARD_SIZE> colSet = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    std::array<std::bitset<Board::BOARD_SIZE>, Board::BOARD_SIZE> blockSet = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

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

    OptimizedBacktrackSolver(board, rowSet, colSet, blockSet);
#endif
#if 0
    BacktrackSolver(board);
#endif
}

void Sudoku::Generate(Difficulty difficulty) {
    board.Clear();
    board.GenerateDiagonal();
    board.GenerateOther(0,0);
    board.RemoveDigit(difficulty);
}


std::ostream& operator<<(std::ostream& out, const Sudoku& sudoku) {
    //out << "Round: " << sudoku.currentRound << '\n';
    //out << "Correct: " << sudoku.correctCount << '\n';
    //out << "Wrong: " << sudoku.wrongCount << '\n';
    out << sudoku.board;
	return out;
}

std::istream& operator>>(std::istream& in, Sudoku& sudoku) {
    in >> sudoku.board;
    return in;
}
