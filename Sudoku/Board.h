/// File: Board.h
/// 
/// Declarations of Board class.   
/// Member functions are helping function for generating and solving sudoku puzzle.
/// 
///	Author: Lazar Nagulov 
/// Last modified: 19.12.2023.

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
	
	bool IsValid() const;
	int CountErrors(const Board& original) const;
	bool IsPossibleMove(int row, int col, int number) const;
	bool FindEmpty(int& row, int& col);
	void GenerateDiagonal();
	bool GenerateOther(int row, int col);
	void FillBlock(int row, int col);
	void RemoveNumber(int count);
	/// <summary>
	/// Sets all elements in board to 0.
	/// </summary>
	void Clear();
	bool Backtrack(BitArray& rowSet, BitArray& colSet, BitArray& blockSet);

	static constexpr int GetBlock(int row, int col);

	const int& operator()(int row, int col) const;
	int& operator()(int row, int col);
	int& At(int row, int col);
	const int& At(int row, int col) const;

	friend std::istream& operator>>(std::istream& in, Board& board);
	friend std::ostream& operator<<(std::ostream& out, const Board& board);
	friend std::ofstream& operator<<(std::ofstream& out, const Board& board);
private:
	int board[BOARD_SIZE * BOARD_SIZE];
};