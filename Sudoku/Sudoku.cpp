/// Sudoku.cpp
/// 
/// Definitions for the Sudoku class, the main class operating with the Board class and providing a user interface.
/// 
/// Author: Lazar Nagulov
/// Last modified: 23rd December 2023.

#include <array>
#include <bitset>
#include <string>
#include <cstdlib>

#include "Sudoku.h"5
#include "Timer.h"

/// <summary>
/// Main constructor for Sudoku class.
/// </summary>
/// <param name="inputFile"> Input file name</param>
/// <param name="outputFile"> Output file name</param>
Sudoku::Sudoku(std::string& inputFile, std::string& outputFile)
    : correctCount(0), wrongCount(0), currentRound(1), emptyCount(0), inputFile(inputFile), outputFile(outputFile) {}
Sudoku::~Sudoku() {}


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

void Sudoku::SolvingOptions() {
    std::cout << "1 > Import solution" << std::endl;
    std::cout << "2 > Solve" << std::endl;
    std::cout << "3 > Exit" << std::endl;

    int ans;
    std::cout << ">> ";
    std::cin >> ans;
    if (ans == 1) {
        CheckSolution();
    }
    else if (ans == 2) {
        Solve();
    }
    else if (ans == 3) {
        exit(0);
    }
    else {
        std::cerr << "Invalid command" << std::endl;
    }
    ++currentRound;
}

void Sudoku::CheckSolution() {
    std::ifstream in(inputFile);
    Board loaded;
    in >> loaded;

    std::cout << "Imported solution" << std::endl;
    std::cout << loaded;
    
    wrongCount = loaded.CountErrors(board);
    std::cout << *this << std::endl;
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
/// Solves the current state of the Sudoku puzzle using a backtracking algorithm.
/// The solved puzzle is written to the specified output file.
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
 
    std::ofstream out(outputFile);
    out << board;
}

/// <summary>
/// Generates a Sudoku puzzle with the specified difficulty level.
/// </summary>
/// <param name="difficulty">Difficulty level of the Sudoku puzzle.</param>
void Sudoku::Generate(Difficulty difficulty) {
    board.Clear();
    emptyCount = difficulty;
    board.GenerateDiagonal();
    board.GenerateOther(0,0);
    board.RemoveNumber(difficulty);
}

/// <summary>
/// Writes the current state of a Sudoku game, including the round number, correct and wrong counts, to the output stream.
/// </summary>
/// <param name="out">Reference to the output stream.</param>
/// <param name="sudoku">Reference to the const Sudoku object to be written.</param>
/// <returns>Reference to the output stream after writing the game state.</returns>
std::ostream& operator<<(std::ostream& out, const Sudoku& sudoku) {
    out << "Round: " << sudoku.currentRound << '\n';
    out << "Correct: " << sudoku.correctCount << '\n';
    out << "Wrong: " << sudoku.wrongCount << '\n';
	return out;
}
