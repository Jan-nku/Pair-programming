#pragma once
#include<string>
#include<iostream>
//定义常量
const int MIN_HOLE = 20;
const int MAX_HOLE = 60;
const int SIZE = 9;

//part5：TODO
// Sudoku class complete the generation of the Sudoku board： -c、-n、-m、-r、-u
class Sudoku {
private:
	static int min_hole;
	static int max_hole;
	int board[SIZE][SIZE];//-1表示丢弃
	int solution_num = 0;
	void initBoard();
	bool fillBoard(int row, int col);
	bool isValid(int row, int col, int num);
	void printBoard();
	void randomLeave();
	bool solveSudoku(int row, int col);
public:
	static void set_level(int level);
	static void set_range(int lower_bound, int upper_bound);
	void writeBoardToFile(std::string file_name);//write sudoku board to the given file
	Sudoku(bool is_final = true, bool is_unique = false);
	Sudoku(std::string file_name);
};