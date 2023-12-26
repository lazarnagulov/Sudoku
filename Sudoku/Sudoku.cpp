/// Sudoku.cpp
/// 
/// Definitions for the Sudoku class, the main class operating with the Board class and providing a user interface.
/// 
/// Author: Lazar Nagulov
/// Last modified: 25th December 2023

#include <array>
#include <bitset>
#include <string>
#include <exception>

#include "Sudoku.h"5
#include "Timer.h"


Sudoku::Sudoku(const std::string& inputFile, const std::string& outputFile)
    : correctCount(0), wrongCount(0), currentRound(1), inputFile(inputFile), outputFile(outputFile) {
}

void Sudoku::Run() {
    while (true) {
        std::cout << std::endl;
        std::cout << "Welcome to \"Sudokusphere\" Sudoku Solver!" << std::endl;
        std::cout << "1 > Generate new Sudoku puzzle" << std::endl;
        std::cout << "2 > Load Sudoku puzzle from file" << std::endl;
        std::cout << "3 > Exit" << std::endl;

        int ans;
        do {
            std::cout << ">> ";
            std::cin >> ans;
            if (ans == 1) {
                Generate(Difficulty::HARD);
                std::ofstream out(outputFile);
                out << board;
                std::cout << board << std::endl;
                out.close();
                SolvingOptions();
                break;
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
                break;
            }
            else if (ans == 3) {
                exit(0);
            }
            else {
                std::cerr << "Invalid command" << std::endl;
            }
        } while (true);
    }
}

void Sudoku::SolvingOptions() {
    std::cout << "Solve puzzle" << std::endl;
    std::cout << "1 > Import solution" << std::endl;
    std::cout << "2 > Solve" << std::endl;
    std::cout << "3 > Exit" << std::endl;

    int ans;
    do {
        std::cout << ">> ";
        std::cin >> ans;
        if (ans == 1) {
            CheckSolution();
            break;
        }
        else if (ans == 2) {
            Solve();
            break;
        }
        else if (ans == 3) {
            exit(0);
            break;
        }
        else {
            std::cerr << "Invalid command" << std::endl;
        }
    } while (true);
    std::cout << "Solution:" << std::endl;
    std::cout << board << std::endl;
    std::cout << *this << std::endl;
    ++currentRound;
}

void Sudoku::CheckSolution() {
    std::ifstream in(inputFile);
    Board loaded;
    in >> loaded;

    std::cout << "Imported solution" << std::endl;
    std::cout << loaded;
    
    // Calculate statistics
    int total = Board::BOARD_SIZE * Board::BOARD_SIZE;
    int emptyCount = loaded.CountEmpty();
    int clues =  total - board.CountEmpty();
    wrongCount = loaded.CountErrors(board);
    
    correctCount = total - wrongCount - emptyCount  - clues;
}

/*
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
*/

bool Sudoku::Solve() {
    Board::BitArray rowSet;
    Board::BitArray colSet;
    Board::BitArray blockSet;


    // Fill BitArrays
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

    if (!board.IsValid()) {
        std::cerr << "Error: Could not solve the puzzle!" << std::endl;
        return false;
    }
 
    std::ofstream out(outputFile);
    out << board;
    out.close();
    return true;
}

void Sudoku::Generate(Difficulty difficulty) {
    board.Clear();
    board.GenerateDiagonal();
    board.GenerateOther(0,0);
    board.RemoveNumber(static_cast<int>(difficulty));
}

/// <summary>
/// Writes the current state of a Sudoku game, including the round number, correct and wrong counts, to the output stream.
/// </summary>
/// <param name="out">Reference to the output stream.</param>
/// <param name="sudoku">Reference to the const Sudoku object to be written.</param>
/// <returns>Reference to the output stream after writing the game state.</returns>
std::ostream& operator<<(std::ostream& out, const Sudoku& sudoku) {
    out << "Results:" << '\n';
    out << "Round: " << sudoku.currentRound << '\n';
    out << "Correct: " << sudoku.correctCount << '\n';
    out << "Wrong: " << sudoku.wrongCount << '\n';
	return out;
}
