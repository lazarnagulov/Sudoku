# Sudoku

## Task
Implement a console application in C++ (C++17) that allows solving and generating Sudoku puzzles. The user inputs files through command-line arguments.

Example program execution:
```bash
./sudoku input.txt output.txt
```
Arguments:

1. input.txt - File from which the puzzle is read.
2. output.txt - File to which the puzzle is written.

Each file contains one puzzle, each row represents a row in the table, and each cell is separated by a space. If files are not specified or do not exist, the user is shown how to use the program.

After successfully running the program, it displays an initial menu with the following options:

- Generate new Sudoku puzzle - Generate a new puzzle.
- Load Sudoku puzzle from file - Load a puzzle.
- Exit - Exit the game.

The generated puzzle is written to the output.txt file. Puzzle is loaded from input file. After generating or loading the puzzle, the user can:

- Import solution - Load a solution.
- Solve -  Allow the program to solve the puzzle.
- Exit - Exit the game.

In the console application, after the program generates a solution or loads one from a file, game statistics are displayed, including the number of correctly placed cells, the number of errors, the game counter, and a list of all found errors. After finishing the game, the user has the option to choose to play again, initiating a new game iteration.

## Testing
Tests are run with the command:
```bash
./sudoku -test [folder_name]
```
Optional argument:
1. folder_name - Folder that contains all tests.

Test files:
- invalid_row.txt
- invalid_column.txt
- invalid_block.txt
- valid.txt
- original_changed.txt & error_changed.txt
- original_column.txt & error_column.txt
- original_row.txt & error_row.txt
- original_block.txt & error_block.txt
- original_all_[i].txt & error_all_[i].txt, for i ∈ [1, 3]

Default test folder is:
```bash
../../Testovi
```
