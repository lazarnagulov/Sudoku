/// File: Test.h
/// 
/// Definitions of Tests.
/// 
///	Author: Lazar Nagulov 
/// Last modified: 23rd December 2023.

#pragma once
#include <string>

#include "Sudoku.h"

/// Tests board validation
std::string TestInvalidColumn();
std::string TestInvalidRow();
std::string TestInvalidBlock();
std::string TestChangedValue();
std::string TestValid();
/// Test possible moves
std::string TestPossibleMoves();
/// Tests board error counting
std::string TestErrorCountAll();
std::string TestRow();
std::string TestColumn();
std::string TestBlock();
std::string TestChangedValue();
/// Tests generation and solvability
std::string TestGenerateAndSolve();

/// <summary>
/// Run all tests.
/// </summary>
void TestRun();



