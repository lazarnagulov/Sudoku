/// Test.h
/// 
/// Definitions of Tests.
/// 
///	Author: Lazar Nagulov 
/// Last modified: 25th December 2023.

#pragma once
#include <string>

#include "Sudoku.h"

/// Tests board validation
std::string TestInvalidColumn(const std::string& path);
std::string TestInvalidRow(const std::string& path);
std::string TestInvalidBlock(const std::string& path);
std::string TestChangedValue(const std::string& path);
std::string TestValid(const std::string& path);
/// Tests board error counting
std::string TestErrorCountAll(const std::string& path);
std::string TestRow(const std::string& path);
std::string TestColumn(const std::string& path);
std::string TestBlock(const std::string& path);
std::string TestChangedValue(const std::string& path);
/// Tests generation and solvability
std::string TestGenerateAndSolve();

/// <summary>
/// Run all tests.
/// </summary>
void TestRun(const std::string& path);



