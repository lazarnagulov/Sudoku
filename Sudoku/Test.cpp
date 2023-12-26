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
std::string TestInvalidColumn(const std::string& testFolder) {
	std::string result;

	std::string inputFile(testFolder + "/invalid_column.txt");
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
std::string TestInvalidRow(const std::string& testFolder) {
	std::string result;

	std::string inputFile(testFolder + "/invalid_row.txt");
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
std::string TestInvalidBlock(const std::string& testFolder) {
	std::string result;

	std::string inputFile(testFolder + "/invalid_block.txt");
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

std::string TestValid(const std::string& testFolder) {
	std::string inputFile(testFolder + "/valid.txt");
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
std::string TestChangedValue(const std::string& testFolder) {
	int wrong = CheckErrors(testFolder + "/original_changed.txt", testFolder + "/error_changed.txt");
	std::cout << "Total errors: " << wrong << std::endl;
	if (wrong != 3) {
		return "Fail - Expected wrong count to be 3 but got " + std::to_string(wrong) + ".";
	}
	return "Pass";
}

std::string TestRow(const std::string& testFolder) {
	int wrong = CheckErrors(testFolder + "/original_row.txt", testFolder + "/error_row.txt");
	std::cout << "Total errors: " << wrong << std::endl;
	if (wrong != 4) {
		return "Fail - Expected wrong count to be 4 but got " + std::to_string(wrong) + ".";
	}

	return "Pass";
}

std::string TestColumn(const std::string& testFolder) {
	int wrong = CheckErrors(testFolder + "/original_column.txt", testFolder + "/error_column.txt");
	std::cout << "Total errors: " << wrong << std::endl;
	if (wrong != 4) {
		return "Fail - Expected wrong count to be 4 but got " + std::to_string(wrong) + ".";
	}

	return "Pass";
}

std::string TestBlock(const std::string& testFolder) {
	int wrong = CheckErrors(testFolder + "/original_block.txt", testFolder + "/error_block.txt");
	std::cout << "Total errors: " << wrong << std::endl;
	if (wrong != 2) {
		return "Fail - Expected wrong count to be 2 but got " + std::to_string(wrong) + ".";
	}

	return "Pass";
}

std::string TestErrorCountAll(const std::string& testFolder) {
	int wrong = CheckErrors(testFolder + "/original_all_1.txt", testFolder + "/error_all_1.txt");
	std::cout << "Total errors: " << wrong << std::endl;
	if (wrong != 4) {
		return "Fail - Expected wrong count to be 4 but got " + std::to_string(wrong) + ".";
	}

	wrong = CheckErrors(testFolder + "/original_all_2.txt", testFolder + "/error_all_2.txt");
	std::cout << "Total errors: " << wrong << std::endl;
	if (wrong != 4) {
		return "Fail - Expected wrong count to be 4 but got " + std::to_string(wrong) + ".";
	}

	wrong = CheckErrors(testFolder + "/original_all_3.txt", testFolder + "/error_all_3.txt");
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


void TestRun(const std::string& path) {
	std::string result;

	std::cout << "-----" << std::endl;

	std::cout << "TestValid" << std::endl;
	std::cout << "-----" << std::endl;
	result = TestValid(path);
	std::cout << ">>>> " << result << " <<<<" << std::endl;

	std::cout << "TestInvalidColumn" << std::endl;
	std::cout << "-----" << std::endl;
	result = TestInvalidColumn(path);
	std::cout << "-----" << std::endl;
	std::cout << ">>>> " << result << " <<<<" << std::endl;

	std::cout << "TestInvalidRow" << std::endl;
	std::cout << "-----" << std::endl;
	result = TestInvalidRow(path);
	std::cout << ">>>> " << result << " <<<<" << std::endl;

	std::cout << "TestInvalidBlock" << std::endl;
	std::cout << "-----" << std::endl;
	result = TestInvalidBlock(path);
	std::cout << ">>>> " << result << " <<<<" << std::endl;

	std::cout << "TestChangedValue" << std::endl;
	std::cout << "-----" << std::endl;
	result = TestChangedValue(path);
	std::cout << ">>>> " << result << " <<<<" << std::endl;

	std::cout << "TestRow" << std::endl;
	std::cout << "-----" << std::endl;
	result = TestRow(path);
	std::cout << ">>>> " << result << " <<<<" << std::endl;

	std::cout << "TestColumn" << std::endl;
	std::cout << "-----" << std::endl;
	result = TestColumn(path);
	std::cout << ">>>> " << result << " <<<<" << std::endl;

	std::cout << "TestBlock" << std::endl;
	std::cout << "-----" << std::endl;
	result = TestBlock(path);
	std::cout << ">>>> " << result << " <<<<" << std::endl;

	std::cout << "TestErrorCountAll" << std::endl;
	std::cout << "-----" << std::endl;
	result = TestErrorCountAll(path);
	std::cout << ">>>> " << result << " <<<<" << std::endl;

	std::cout << "TestGenerateAndSolve" << std::endl;
	std::cout << "-----" << std::endl;
	result = TestGenerateAndSolve();
	std::cout << ">>>> " << result << " <<<<" << std::endl;

	std::cout << "End of tests!" << std::endl;
}

