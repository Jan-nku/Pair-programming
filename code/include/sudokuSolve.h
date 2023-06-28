#pragma once
#include<string>
#include<iostream>
class SudokuSolve {
private:
	int board[9][9];//-1±íÊ¾¶ªÆú
	bool solve(int row, int col);
public:
	void readFromFile(std::ifstream& file);
	void writeToFile(std::ofstream& file);
	bool solve();
};

void solveSudokuFile(const std::string inputFilePath, const std::string outputFilePath = "sudoku.txt");


