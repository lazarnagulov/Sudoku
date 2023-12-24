/// Board.h
/// 
/// Declarations for the Board class, which includes member functions for generating and solving Sudoku puzzles.
/// 
/// Author: Lazar Nagulov
/// Last modified: 23rd December 2023

#pragma once
#include <iostream>
#include <bitset>
#include <array>
#include <fstream>

class Board {
public:
	Board();
	~Board();

	static const int BOARD_SIZE = 9;
	static const int BLOCK_SIZE = 3;
	static const int EMPTY = 0;
	static const char EMPTY_CHAR = '_';

	using BitArray = std::array<std::bitset<Board::BOARD_SIZE>, Board::BOARD_SIZE>;
	using PairArray = std::array<std::pair<int, int>, BOARD_SIZE>;

	/// <summary>
	/// Checks if the current board is valid.
	/// </summary>
	/// <returns>True if the current board is valid.</returns>
	bool IsValid() const;
	
	/// <summary>
	/// Counts and reports the number of errors in the current Sudoku board by checking rows, columns, and blocks.
	/// </summary>
	/// <param name="checking">Original board to check for errors.</param>
	/// <returns>The number of errors found in the board.</returns>
	int CountErrors(const Board& original);
	

	/// <summary>
	/// Finds the first empty cell in the board and updates the row and column parameters.
	/// </summary>
	/// <param name="row">Reference to the variable to store the row index of the empty cell.</param>
	/// <param name="col">Reference to the variable to store the column index of the empty cell.</param>
	/// <returns>True if an empty cell is found, false otherwise.</returns>
	bool FindEmpty(int& row, int& col);
	

	int CountEmpty();

	/// <summary>
	/// Generates a Sudoku board with diagonal blocks filled.
	/// Diagonal blocks are filled using the FillBlock function starting from the top-left corner.
	/// </summary>
	void GenerateDiagonal();
	
	/// <summary>
	/// Generates a puzzle by recursively solving the board using backtracking.
	/// </summary>
	/// <param name="row">Current row index in the board.</param>
	/// <param name="col">Current column index in the board.</param>
	/// <returns>True if a valid puzzle is successfully generated, false otherwise.</returns>
	bool GenerateOther(int row, int col);
	

	/// <summary>
	/// Randomly removes numbers from the board to create a puzzle with the specified count of empty cells.
	/// </summary>
	/// <param name="count">Number of cells to remove from the board.</param>
	void RemoveNumber(int count);	
	
	/// <summary>
	/// Sets all elements in board to 0.
	/// </summary>
	void Clear();
	
	/// <summary>
	/// Recursive backtracking algorithm to solve the Sudoku board.
	/// </summary>
	/// <param name="rowSet">BitArray representing the numbers used in each row.</param>
	/// <param name="colSet">BitArray representing the numbers used in each column.</param>
	/// <param name="blockSet">BitArray representing the numbers used in each block.</param>
	/// <returns>True if the board is successfully solved, false otherwise.</returns>
	bool Backtrack(BitArray& rowSet, BitArray& colSet, BitArray& blockSet);

	/// <summary>
	/// Determines the block index (zero-based) for a given cell position in the board.
	/// </summary>
	/// <param name="row">Row index of the cell.</param>
	/// <param name="col">Column index of the cell.</param>
	/// <returns>The block index for the specified cell position.</returns>
	static inline int GetBlock(int row, int col);

	/// <summary>
	/// Provides read-only access to the value at the specified cell in the board.
	/// </summary>
	/// <param name="row">Row index of the cell.</param>
	/// <param name="col">Column index of the cell.</param>
	/// <returns>Constant reference to the value at the specified cell.</returns>
	const int& operator()(int row, int col) const;
	
	/// <summary>
	/// Provides read and write access to the value at the specified cell in the Sudoku board.
	/// </summary>
	/// <param name="row">Row index of the cell.</param>
	/// <param name="col">Column index of the cell.</param>
	/// <returns>Reference to the value at the specified cell.</returns>
	int& operator()(int row, int col);

	/// <summary>
	/// Provides a reference to the value at the specified cell in the Sudoku board.
	/// Throws an out_of_range exception if the indices are out of the valid range.
	/// </summary>
	/// <param name="row">Row index of the cell.</param>
	/// <param name="col">Column index of the cell.</param>
	/// <returns>Reference to the value at the specified cell.</returns>
	int& At(int row, int col);
	
	/// <summary>
	/// Provides a constant reference to the value at the specified cell in the Sudoku board.
	/// Throws an out_of_range exception if the indices are out of the valid range.
	/// </summary>
	/// <param name="row">Row index of the cell.</param>
	/// <param name="col">Column index of the cell.</param>
	/// <returns>Constant reference to the value at the specified cell.</returns>
	const int& At(int row, int col) const;

	friend std::istream& operator>>(std::istream& in, Board& board);
	friend std::ostream& operator<<(std::ostream& out, const Board& board);
	friend std::ofstream& operator<<(std::ofstream& out, const Board& board);
private:
	/// <summary>
	/// Checks if the number at the specified cell in the board is a duplicate within its row, column or block.
	/// Keeps track of the first occurrence of each number in the given buffer.
	/// </summary>
	/// <param name="row">Row index of the cell.</param>
	/// <param name="col">Column index of the cell.</param>
	/// <param name="buff">Buffer to track the first occurrence of each number.</param>
	/// <returns>True if the number is a duplicate, false otherwise.</returns>
	bool IsDuplicate(int row, int col, PairArray& buff);

	/// <summary>
	/// Fills a block starting from the specified position with random numbers from 1 to BOARD_SIZE.
	/// </summary>
	/// <param name="row">Starting row index of the block.</param>
	/// <param name="col">Starting column index of the block.</param>
	void FillBlock(int row, int col);

	/// <summary>
	/// Checks if placing a given number at the specified position in the board is a valid move.
	/// </summary>
	/// <param name="row">Row index of the position.</param>
	/// <param name="col">Column index of the position.</param>
	/// <param name="number">Number to be checked for validity.</param>
	/// <returns>True if placing the number is a valid move, false otherwise.</returns>
	bool IsPossibleMove(int row, int col, int number) const;
private:
	int board[BOARD_SIZE * BOARD_SIZE];
};