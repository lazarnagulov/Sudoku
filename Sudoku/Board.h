/// File: Board.h
/// 
/// Declarations of Board class.   
/// Member functions are helping function for generating and solving sudoku puzzle.
/// 
///	Author: Lazar Nagulov 
/// Last modified: 27.12.2023.

#pragma once
#include <cmath>
#include <iostream>
#include <fstream>

class Board {
public:
	Board();
	~Board();

	static const int BOARD_SIZE = 9;
	static const int BLOCK_SIZE = 3;
	static const int EMPTY = 0;
	static const char EMPTY_CHAR = '_';

	bool IsValid() const;
	int CountErrors() const;
	bool IsPossibleMove(int row, int col, int number) const;
	bool FindEmpty(int& row, int& col);
	void GenerateDiagonal();
	bool GenerateOther(int row, int col);
	void FillBlock(int row, int col);
	void RemoveDigit(int count);
	void Clear();

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