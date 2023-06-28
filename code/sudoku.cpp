#include"sudoku.h"
#include<vector>
#include<random>
#include <algorithm>
#include<fstream>
#include<ostream>

int Sudoku::min_hole = 20;
int Sudoku::max_hole = 30;

//set game_level if -m, actually equals to -r
void Sudoku::set_level(int level) {
	switch (level) {
	case 1:
		min_hole = 20;
		max_hole = 30;
		break;
	case 2:
		min_hole = 30;
		max_hole = 40;
		break;
	case 3:
		min_hole = 40;
		max_hole = 50;
		break;
	default:
		break;
	}
}

//set lower_bound and upper_bound if -r, used to control the game level
void Sudoku::set_range(int lower_bound, int upper_bound) {
	min_hole = lower_bound;
	max_hole = upper_bound;
}

//Constructor: generate a sudoku board, set is_final true if -n, set is_unique true if -u
Sudoku::Sudoku(bool is_final, bool is_unique) {
    // Initialize and fill board
    initBoard();
    fillBoard(0, 0);
    if (is_final) {
        return;
    }
    else {
        randomLeave();
    }
    if (is_unique) {
        //TODO: Deal with the situation where there is only one solution to Sudoku
        solution_num = 0;
        solveSudoku(0, 0);
        while (solution_num > 1) {
            initBoard();
            fillBoard(0, 0);
            randomLeave();
            solution_num = 0;
            solveSudoku(0, 0);
        }
        return;
    }
}

//Constructor: import Sudoku board from file
Sudoku::Sudoku(std::string file_name) {
    initBoard();
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_name << std::endl;
        return;
    }
    std::string line;
    int row = 0;
    while (std::getline(file, line)) {
        for (int col = 0; col < SIZE; col++) {
            char c = line[col];
            if (c == '#') {
                board[row][col] = -1;
            }
            else {
                board[row][col] = c - '0';
            }
        }
        row++;
        if (row == SIZE)
        {
            break;
        }
    }
    file.close();
}

//print the sudoku board
void Sudoku::printBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == -1) {
                std::cout << "#";
            }
            else {
                std::cout << board[i][j];
            }
        }
        std::cout << std::endl;
    }
}

//Find the number of sudoku solutions and store them in solution_num, unchange the board
bool Sudoku::solveSudoku(int row, int col) {
    if (row == SIZE - 1 && col == SIZE) {
        solution_num++;
        if (solution_num > 1)
            return true;
        return false;
    }
    if (col == SIZE) {
        row++;
        col = 0;
    }
    if (board[row][col] != -1)
        return solveSudoku(row, col + 1);
    for (int num = 1; num <= SIZE; num++) {
        if (isValid(row, col, num)) {
            board[row][col] = num;
            if (solveSudoku(row, col + 1))
                return true;
            //to keep the board unchanged
            board[row][col] = -1;
        }
    }
    return false;
}

//write sudoku board to file
void Sudoku::writeBoardToFile(std::string file_name) {
    std::ofstream file(file_name);
    if (!file.is_open()) {
        std::cout << "Error: could not open file : " << file_name << std::endl;
        return;
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] != -1)
                file << board[i][j] << ' ';
            else
                file << '#' << ' ';
        }
        file << '\n';
    }
    file.close();
}

//init the sudoku board
void Sudoku::initBoard() {
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = 0;
        }
    }
}

//fill board, used to generate a final board
bool Sudoku::fillBoard(int row, int col) {
    // 每行递归
    if (row == SIZE) {
        return true;
    }
    if (col == SIZE) {
        return fillBoard(row + 1, 0);
    }
    if (board[row][col] != 0) {
        return fillBoard(row, col + 1);
    }
    std::vector<int> nums;
    for (int num = 1; num <= SIZE; num++)
    {
        if (isValid(row, col, num)) {
            nums.push_back(num);
        }
    }
    random_shuffle(nums.begin(), nums.end());
    for (auto num : nums)
    {
        board[row][col] = num;
        if (fillBoard(row, col + 1))
        {
            return true;
        }
    }
    board[row][col] = 0;
    return false;
}

//Check whether the filling of the board is valid
bool Sudoku::isValid(int row, int col, int num) {
    // 检查所在行和列是否存在相同数字
    for (int i = 0; i < SIZE; i++)
    {
        if (board[row][i] == num || board[i][col] == num)
        {
            return false;
        }
    }
    // 检查所在的正方块内是否存在相同数字
    int row_start = (row / 3) * 3;
    int col_start = (col / 3) * 3;
    for (int i = row_start; i < row_start + 3; i++)
    {
        for (int j = col_start; j < col_start + 3; j++)
        {
            if (board[i][j] == num)
            {
                return false;
            }
        }
    }
    return true;
}

//Randomly discard some positional elements in Sudoku
void Sudoku::randomLeave() {
    std::random_device rd;
    std::mt19937 gen(rd());
    int num = (rand() % (max_hole - min_hole + 1)) + min_hole;
    bool tempArray[SIZE * SIZE];
    std::fill(tempArray, tempArray + num, false);
    std::fill(tempArray + num, tempArray + SIZE * SIZE, true);
    std::shuffle(tempArray, tempArray + SIZE * SIZE, gen);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (!tempArray[i * SIZE + j]) {
                board[i][j] = -1;
            }
        }
    }
}