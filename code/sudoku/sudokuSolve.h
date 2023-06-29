#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "sudoku.h"

class SudokuSolve
{
private:
	Sudoku sudoku;

public:
	void readFromFile(std::ifstream& file);
	void writeToFile(std::ofstream& file);
	bool solveSudoku();
	void solveSudokuFile(const std::string& inputFilePath, const std::string& outputFilePath = "sudoku.txt");
};
