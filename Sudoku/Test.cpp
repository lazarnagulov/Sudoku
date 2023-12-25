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
	if (wrong != 3) {
		return "Fail - Expected wrong count to be 3 but got " + std::to_string(wrong) + ".";
	}
	return "Pass";
}


std::string TestErrorCountAll() {
	int wrong = CheckErrors("../../Testovi/original_all.txt", "../../Testovi/error_all.txt");
	if (wrong != 4) {
		return "Fail - Expected wrong count to be 4 but got " + std::to_string(wrong) + ".";
	}

	wrong = CheckErrors("../../Testovi/original_all_2.txt", "../../Testovi/error_all_2.txt");
	if (wrong != 4) {
		return "Fail - Expected wrong count to be 4 but got " + std::to_string(wrong) + ".";
	}

	wrong = CheckErrors("../../Testovi/original_all_3.txt", "../../Testovi/error_all_3.txt");
	if (wrong != 3) {
		return "Fail - Expected wrong count to be 3 but got " + std::to_string(wrong) + ".";
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

