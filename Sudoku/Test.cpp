#include "Test.h"

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
	std::string result;

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
	Board original;
	Board compare;
	std::string originalFile("../../Testovi/original_changed.txt");
	std::string compareFile("../../Testovi/error_changed.txt");
	std::ifstream inOriginal(originalFile);
	std::ifstream inCompare(compareFile);

	inOriginal >> original;
	inCompare >> compare;

	int wrong = compare.CountErrors(original);

	inOriginal.close();
	inCompare.close();

	if (wrong != 3) {
		return "Fail - Expected wrong count to be 3 but got " + std::to_string(wrong) + ".";
	}

	return "Pass";
}

std::string TestErrorCountAll() {
	Board original;
	Board compare;
	std::string originalFile("../../Testovi/original_all.txt");
	std::string compareFile("../../Testovi/error_all.txt");

	std::ifstream inOriginal(originalFile);
	std::ifstream inCompare(compareFile);

	inOriginal >> original;
	inCompare >> compare;

	int wrong = compare.CountErrors(original);
	
	inOriginal.close();
	inCompare.close();

	if (wrong != 6) {
		return "Fail - Expected wrong count to be 6 but got " + std::to_string(wrong) + ".";
	}

	return "Pass";
}
/// Tests generation
std::string TestGenerate() {
	return "Pass";
}
/// Test Solve
std::string TestSolve() {
	return "Pass";
}

void TestRun() {
	std::string result;
	std::cout << "-----" << std::endl;
	result = TestInvalidColumn();
	std::cout << "TestInvalidColumn >" << result << std::endl;
	std::cout << "-----" << std::endl;

	result = TestInvalidRow();
	std::cout << "TestInvalidRow > " << result << std::endl;
	std::cout << "-----" << std::endl;

	result = TestInvalidBlock();
	std::cout << "TestInvalidBlock > " << result << std::endl;
	std::cout << "-----" << std::endl;

	result = TestChangedValue();
	std::cout << "TestChangedValue > " << result << std::endl;
	std::cout << "-----" << std::endl;

	result = TestErrorCountAll();
	std::cout << "TestErrorCountAll > " << result << std::endl;
	std::cout << "-----" << std::endl;

#if 0
	result = TestValid();
	std::cout << "TestValid > " << result << std::endl;
	result = TestErrorCount();
	std::cout << "TestErrorCount > " << result << std::endl;
	result = TestChangedValue();
	std::cout << "TestChangedValue > " << result << std::endl;
	result = TestGenerate();
	std::cout << "TestGenerate > " << result << std::endl;
	result = TestSolve();
	std::cout << "TestSolve > " << result << std::endl;
#endif
}

