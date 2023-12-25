/// File: Sudoku.h
/// 
/// Declarations of Sudoku class.   
/// Contains a main game functions such as Run, Solve, Generate.
/// 
///	Author: Lazar Nagulov 
/// Last modified: 25rd December 2023
#pragma once
#include <fstream>
#include <bitset>

#include "Board.h"

class Sudoku {
public:
	enum class Difficulty {
		EASY = 43,
		MEDIUM = 50,
		HARD = 56,
		VERY_HARD = 60,
	};

	/// <summary>
	/// Main constructor for Sudoku class.
	/// </summary>
	/// <param name="inputFile"> Input file name</param>
	/// <param name="outputFile"> Output file name</param>
	Sudoku(const std::string& inputFile, const std::string& outputFile);
	~Sudoku() = default;
	Sudoku(const Sudoku&) = delete;

	/// <summary>
	/// Runs the Sudoku game, providing options to generate a new puzzle, load a puzzle from a file, or exit the program.
	/// After generating or loading a puzzle, the user can choose solving options.
	/// </summary>
	void Run();

	/// <summary>
	/// Displays solving options for the Sudoku game and processes the user's choice.
	/// Options include importing a solution, solving the puzzle, or exiting the program.
	/// </summary>
	void SolvingOptions();

	/// <summary>
	/// Solves the current state of the Sudoku puzzle using a backtracking algorithm.
	/// The solved puzzle is written to the specified output file.
	/// </summary>
	/// <returns>True solution is found.</returns>
	bool Solve();

	/// <summary>
	/// Compares the loaded solution from an input file with the current state of the Sudoku puzzle.
	/// Counts and displays the number of incorrect cells in the current state.
	/// </summary>
	void CheckSolution();

	/// <summary>
	/// Generates a Sudoku puzzle with the specified difficulty level.
	/// </summary>
	/// <param name="difficulty">Difficulty level of the Sudoku puzzle.</param>
	void Generate(Difficulty difficulty);

	friend std::ostream& operator<<(std::ostream& out, const Sudoku& sudoku);
private:
	const std::string inputFile;
	const std::string outputFile;

	int currentRound;
	int correctCount;
	int wrongCount;

	Board board;
};
