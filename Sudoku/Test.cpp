/// Test.cpp
/// 
/// Test implementations.
/// 
///	Author: Lazar Nagulov 
/// Last modified: 25th December 2023.

#include "Test.h"


static int CheckErrors(const std::string& originalFile, const std::string& compareFile) {
	Board original;
	Board compare;

	std::ifstream inOriginal(originalFile);
	std::ifstream inCompare(compareFile);

	inOriginal >> original;
	inCompare >> compare;

	int wrong = compare.CountErrors(original);

	inOriginal.close();
	inCompare.close();
	return wrong;
}

/// Tests board validation
std::string TestInvalidColumn() {
	std::string result;

	std::string inputFile("../../Testovi/invalid_column.txt");
	std::ifstream in(inputFile);
	Board b;
	in >> b;
	
	bool valid = b.IsValid();
	if (!valid) {
		return "Pass";
	}
	else {
		return "Fail";
	}
}
std::string TestInvalidRow() {
	std::string result;

	std::string inputFile("../../Testovi/invalid_row.txt");
	std::ifstream in(inputFile);
	Board b;
	in >> b;

	bool valid = b.IsValid();

	if (!valid) {
		return "Pass";
	}
	else {
		return "Fail";
	}
}
std::string TestInvalidBlock() {
	std::string result;

	std::string inputFile("../../Testovi/invalid_block.txt");
	std::ifstream in(inputFile);
	Board b;
	in >> b;

	bool valid = b.IsValid();
	if (!valid) {
		return "Pass";
	}
	else {
		return "Fail";
	}
}
std::string TestPossibleMoves() {
	return "Pass";
}

std::string TestValid() {
	std::string inputFile("../../Testovi/valid.txt");
	std::ifstream in(inputFile);
	Board b;
	in >> b;

	bool valid = b.IsValid();

	if (valid) {
		return "Pass";
	}
	else {
		return "Fail";
	}
}

/// Tests board error counting
std::string TestChangedValue() {
	int wrong = CheckErrors("../../Testovi/original_changed.txt", "../../Testovi/error_changed.txt");
	std::cout << "Total errors: " << wrong << std::endl;
	if (wrong != 3) {
		return "Fail - Expected wrong count to be 3 but got " + std::to_string(wrong) + ".";
	}
	return "Pass";
}

std::string TestRow() {
	int wrong = CheckErrors("../../Testovi/original_row.txt", "../../Testovi/error_row.txt");
	std::cout << "Total errors: " << wrong << std::endl;
	if (wrong != 4) {
		return "Fail - Expected wrong count to be 4 but got " + std::to_string(wrong) + ".";
	}

	return "Pass";
}

std::string TestColumn() {
	int wrong = CheckErrors("../../Testovi/original_column.txt", "../../Testovi/error_column.txt");
	std::cout << "Total errors: " << wrong << std::endl;
	if (wrong != 4) {
		return "Fail - Expected wrong count to be 4 but got " + std::to_string(wrong) + ".";
	}

	return "Pass";
}

std::string TestBlock() {
	int wrong = CheckErrors("../../Testovi/original_block.txt", "../../Testovi/error_block.txt");
	std::cout << "Total errors: " << wrong << std::endl;
	if (wrong != 2) {
		return "Fail - Expected wrong count to be 2 but got " + std::to_string(wrong) + ".";
	}

	return "Pass";
}

std::string TestErrorCountAll() {
	int wrong = CheckErrors("../../Testovi/original_all_1.txt", "../../Testovi/error_all_1.txt");
	std::cout << "Total errors: " << wrong << std::endl;
	if (wrong != 4) {
		return "Fail - Expected wrong count to be 4 but got " + std::to_string(wrong) + ".";
	}

	wrong = CheckErrors("../../Testovi/original_all_2.txt", "../../Testovi/error_all_2.txt");
	std::cout << "Total errors: " << wrong << std::endl;
	if (wrong != 4) {
		return "Fail - Expected wrong count to be 4 but got " + std::to_string(wrong) + ".";
	}

	wrong = CheckErrors("../../Testovi/original_all_3.txt", "../../Testovi/error_all_3.txt");
	std::cout << "Total errors: " << wrong << std::endl;
	if (wrong != 3) {
		return "Fail - Expected wrong count to be 3 but got " + std::to_string(wrong) + ".";
	}

	return "Pass";
}

/// Tests generation
std::string TestGenerateAndSolve() {
	Sudoku s("input.txt", "output.txt");
	for (int i = 0; i < 100; ++i) {
		s.Generate(Sudoku::Difficulty::HARD);
		if (!s.Solve()) 
			return "Fail - Could not solve board " + std::to_string(i) + ".";
	}

	return "Pass";
}


void TestRun() {
	std::string result;
	std::cout << "-----" << std::endl;

	std::cout << "TestValid" << std::endl;
	std::cout << "-----" << std::endl;
	result = TestValid();
	std::cout << ">>>> " << result << " <<<<" << std::endl;

	std::cout << "TestInvalidColumn" << std::endl;
	std::cout << "-----" << std::endl;
	result = TestInvalidColumn();
	std::cout << "-----" << std::endl;
	std::cout << ">>>> " << result << " <<<<" << std::endl;

	std::cout << "TestInvalidRow" << std::endl;
	std::cout << "-----" << std::endl;
	result = TestInvalidRow();
	std::cout << ">>>> " << result << " <<<<" << std::endl;

	std::cout << "TestInvalidBlock" << std::endl;
	std::cout << "-----" << std::endl;
	result = TestInvalidBlock();
	std::cout << ">>>> " << result << " <<<<" << std::endl;

	std::cout << "TestChangedValue" << std::endl;
	std::cout << "-----" << std::endl;
	result = TestChangedValue();
	std::cout << ">>>> " << result << " <<<<" << std::endl;

	std::cout << "TestRow" << std::endl;
	std::cout << "-----" << std::endl;
	result = TestRow();
	std::cout << ">>>> " << result << " <<<<" << std::endl;

	std::cout << "TestColumn" << std::endl;
	std::cout << "-----" << std::endl;
	result = TestColumn();
	std::cout << ">>>> " << result << " <<<<" << std::endl;

	std::cout << "TestBlock" << std::endl;
	std::cout << "-----" << std::endl;
	result = TestBlock();
	std::cout << ">>>> " << result << " <<<<" << std::endl;

	std::cout << "TestErrorCountAll" << std::endl;
	std::cout << "-----" << std::endl;
	result = TestErrorCountAll();
	std::cout << ">>>> " << result << " <<<<" << std::endl;

	std::cout << "TestGenerateAndSolve" << std::endl;
	std::cout << "-----" << std::endl;
	result = TestGenerateAndSolve();
	std::cout << ">>>> " << result << " <<<<" << std::endl;

	std::cout << "End of tests!" << std::endl;
}

