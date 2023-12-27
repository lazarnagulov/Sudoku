/// Sudoku.cpp
/// 
/// Definitions for the Sudoku class, the main class operating with the Board class and providing a user interface.
/// 
/// Author: Lazar Nagulov
/// Last modified: 26th December 2023

#include "Sudoku.h"


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
            std::cout << "Solution:" << std::endl;
            std::cout << board << std::endl;
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

    int total = Board::BOARD_SIZE * Board::BOARD_SIZE;
    int clues = total - board.CountEmpty();

    board.Backtrack(rowSet, colSet, blockSet);
    
    wrongCount = board.CountErrors(board);
    correctCount = total - clues;
    
    if (wrongCount != 0) {
        return false;
    }
    
    std::ofstream out(outputFile);
    out << board;
    out.close();
    return true;
}


static int GetNextDifficulty(Sudoku::Difficulty difficulty) {
    switch (difficulty) {
    case Sudoku::Difficulty::EASY:
        return static_cast<int>(Sudoku::Difficulty::MEDIUM);
        break;
    case Sudoku::Difficulty::MEDIUM:
        return static_cast<int>(Sudoku::Difficulty::HARD);
    case Sudoku::Difficulty::HARD:
        return static_cast<int>(Sudoku::Difficulty::VERY_HARD);
    default:
        return 61;
    }
}

void Sudoku::Generate(Difficulty difficulty) {
    int next = GetNextDifficulty(difficulty);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> random(static_cast<int>(difficulty), next);
    board.Clear();
    board.GenerateDiagonal();
    board.GenerateOther(0,0);
    board.RemoveNumber(random(rng));
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
