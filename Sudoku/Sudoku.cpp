/// File: Sudoku.cpp
/// 
/// Definitions of Sudoku class.
/// Main class that operates with Board class and provied user interface.
/// 
///	Author: Lazar Nagulov 
/// Last modified: 23.12.2023.

#include <array>
#include <bitset>
#include <string>
#include <cstdlib>

#include "Sudoku.h"
#include "Timer.h"


Sudoku::Sudoku(std::string& inputFile, std::string& outputFile)
    : correctCount(0), wrongCount(0), currentRound(1), emptyCount(0), inputFile(inputFile), outputFile(outputFile) {}
Sudoku::~Sudoku() {}

/// <summary>
/// Runs a main game loop.
/// </summary>
void Sudoku::Run() {
    while (true) {
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
            std::ofstream out(outputFile);
            out << board;
            std::cout << board << std::endl;
            out.close();
            SolvingOptions();
        }
        else if (ans == 2) {
            std::ifstream in(inputFile);
            in >> board;
            std::cout << "Loaded puzzle:" << std::endl;
            std::cout << board << std::endl;
            in.close();
            bool valid = board.IsValid();
            if (!valid) {
                std::cout << "Loaded puzzle is not valid!" << std::endl;
                continue;
            }
            SolvingOptions();
        }
        else if (ans == 3) {
            exit(0);
        }
        else {
            std::cerr << "Invalid command" << std::endl;
        }
    }
}


/// <summary>
/// Gives user a solving options.
/// </summary>
void Sudoku::SolvingOptions() {
    std::cout << "1 > Import solution" << std::endl;
    std::cout << "2 > Solve" << std::endl;
    std::cout << "3 > Exit" << std::endl;

    int ans;
    std::cout << ">> ";
    std::cin >> ans;
    if (ans == 1) {
        std::ifstream in(inputFile);
        CheckSolution(in);
        in.close();
    }
    else if (ans == 2) {
        std::ofstream out(outputFile);
        Board curr = board;
        Solve();
        wrongCount = board.CountErrors(curr);
        correctCount = Board::BOARD_SIZE * Board::BOARD_SIZE - emptyCount - wrongCount;
        out << board;
        std::cout << *this << std::endl;
        out.close();
    }
    else if (ans == 3) {
        exit(0);
    }
    else {
        std::cerr << "Invalid command" << std::endl;
    }
    ++currentRound;
}


/// <summary>
/// Checks if solution provided by user.
/// Prints an error and total error count.
/// </summary>
/// <param name="in">
/// Solution input file.
/// </param>
void Sudoku::CheckSolution(std::ifstream& in) {
    Board loaded;
    in >> loaded;
    std::cout << "Imported solution" << std::endl;
    std::cout << loaded;
    wrongCount = board.CountErrors(loaded);
    correctCount = Board::BOARD_SIZE * Board::BOARD_SIZE - emptyCount - wrongCount;
    std::cout << "Wrong: " << wrongCount << std::endl;
    std::cout << "Correct: " << correctCount << std::endl;
}


static bool Backtrack(Board& board) {
    int row, col;
    if (!board.FindEmpty(row, col)) {
        return true;
    }
    for (int number = 1; number <= Board::BOARD_SIZE; ++number) {
        if (board.IsPossibleMove(row, col, number)) {
            board(row, col) = number;
            if (Backtrack(board)) {
                return true;
            }
            board(row, col) = Board::EMPTY;
        }
    }
    return false;
}

/// <summary>
/// Solves sudoku puzzle using optimized Backtracking algorithm.
/// </summary>
void Sudoku::Solve() {
    Board::BitArray rowSet;
    Board::BitArray colSet;
    Board::BitArray blockSet;

    for (int row = 0; row < Board::BOARD_SIZE; ++row) {
        for (int col = 0; col < Board::BOARD_SIZE; ++col) {
            int number = board(row, col);
            if (number != Board::EMPTY) {
                int idx = number - 1;
                rowSet[row].set(idx);
                colSet[col].set(idx);
                int blockIdx = Board::GetBlock(row, col);
                blockSet[blockIdx].set(idx);
            }
        }
    }

    board.Backtrack(rowSet, colSet, blockSet);
}

/// <summary>
/// Generates puzzle with given difficulty.
/// </summary>
/// <param name="difficulty">
/// Puzzle difficulty
/// </param>
void Sudoku::Generate(Difficulty difficulty) {
    board.Clear();
    emptyCount = difficulty;
    board.GenerateDiagonal();
    std::cout << board << std::endl;
    board.GenerateOther(0,0);
    std::cout << board << std::endl;;
    board.RemoveNumber(difficulty);
    std::cout << board << std::endl;;
}

std::ostream& operator<<(std::ostream& out, const Sudoku& sudoku) {
    out << "Round: " << sudoku.currentRound << '\n';
    out << "Correct: " << sudoku.correctCount << '\n';
    out << "Wrong: " << sudoku.wrongCount << '\n';
    out << sudoku.board;
	return out;
}
