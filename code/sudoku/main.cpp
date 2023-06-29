#include<iostream>
#include<ctime>
#include<string>
#include <fstream>
#include <direct.h>
#include <io.h>

#include"getopt.h"
#include"sudoku.h"
#include"sudokuSolve.h"

#define u_int unsigned int

//part1:TODO
/*设置全局变量存储sudoku参数*/

//-c需要的数独终盘数量
bool opt_gen_final = false;
int final_num = 0;//限制范围在1-1000000

//-s需要解的数独棋盘文件路径
bool opt_solve = false;
char solve_file_path[256] = "";

//-n需要的游戏数量
bool opt_number = false;
int game_num = 0;//限制在1-10000

//-m生成游戏的难度<->挖空数量,需要和-n一同使用
bool opt_level = false;
int game_level = 0;

//-r生成游戏中挖空的数量范围，需要和-n一同使用
bool opt_range = false;
u_int min_hole_num = MIN_HOLE;
u_int max_hole_num = MAX_HOLE;

//-u生成唯一解，需要和-n一同使用
bool opt_unique = false;

//Define an assert function, which is directly defined in the main function for convenience
void Assert(bool cond, const std::string& error = "") {
	if (!cond) {
		std::cout << error << std::endl;
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char* argv[]) {
	srand(time(nullptr));
	//part2:TODO
	/*option parser借用getopt库，将解析后的参数存储到变量中*/
	int opt;//option选项
	char opt_arg[256];//存储参数
	char args[] = "c:s:n:m:r:u";
	while ((opt = getopt(argc, argv, args)) != -1) {
		switch (opt) {
		case 'c':
			Assert(!opt_gen_final, "duplicated opt:c");
			opt_gen_final = true;
			final_num = atoi(optarg);
			break;
		case 's':
			Assert(!opt_solve, "duplicated opt:s");
			opt_solve = true;
			strcpy(solve_file_path, optarg);
			break;
		case 'n':
			Assert(!opt_number, "duplicated opt:n");
			opt_number = true;
			game_num = atoi(optarg);
			break;
		case 'm':
			Assert(!opt_level, "duplicated opt:m");
			opt_level = true;
			game_level = atoi(optarg);
			break;
		case 'r':
			Assert(!opt_range, "duplicated opt:r");
			opt_range = true;
			strcpy(opt_arg, optarg);
			char* num;
			num = std::strtok(opt_arg, "~");
			min_hole_num = atoi(num);
			num = std::strtok(NULL, "~");
			max_hole_num = atoi(num);
			break;
		case 'u':
			Assert(!opt_unique, "duplicated opt:u");
			opt_unique = true;
			break;
		default:
			printf("Invalid Args: %c\n", opt);
			exit(EXIT_FAILURE);
			break;
		}
	}

	//part3:TODO
	/*check args*/
	if (opt_gen_final) {
		Assert(final_num > 0, "游戏终局数量需要 > 0 !");
		Assert(final_num <= 1000000, "游戏终局数量需要 < 1000000 !");
	}
	if (opt_number) {
		Assert(game_num > 0, "游戏数量需要 > 0");
		Assert(game_num <= 10000, "游戏数量需要 < 10000");
	}
	if (opt_level) {
		Assert(opt_number, "opt-m 需要opt-n");
		Assert((game_level == 1 || game_level == 2 || game_level == 3), "游戏等级取值为 1,2,3 !");
	}
	if (opt_range) {
		Assert(opt_number, "opt-r 需要opt-n");
		Assert(min_hole_num <= max_hole_num, "挖空数量上下界错误");
		Assert(MIN_HOLE <= min_hole_num, "挖空数量下界小于最小值");
		Assert(MAX_HOLE >= max_hole_num, "挖空数量上界大于最大值");
	}
	if (opt_unique) {
		Assert(opt_number, "opt-u 需要opt-n");
	}

	//part4：TODO
	/*Execute commands based on the parameters*/
	//define interface to complete
	if (opt_gen_final) {
		//use library <direct.h> and <io.h> to operate file
		if (_access("./final", 0) == -1) {
			if (_mkdir("./final") == -1) {
				printf("_makir ./final error!");
				exit(EXIT_FAILURE);
			}
		}
		std::string file_names = "./final/final_game_";
		for (int i = 1; i <= final_num; i++) {
			Sudoku temp = Sudoku();
			temp.writeBoardToFile(file_names + std::to_string(i) + ".txt");
		}
	}
	if (opt_solve) {
		SudokuSolve sudokuSolve;
		sudokuSolve.solveSudokuFile(solve_file_path);
	}
	if (opt_number) {
		if (_access("./games", 0) == -1)
			if (_mkdir("./games") == -1) {
				printf("_makir ./games error!");
				exit(EXIT_FAILURE);
			}
		std::string file_names = "./games/game_";
		if (opt_level) {
			Sudoku::set_level(game_level);
		}
		if (opt_range) {
			Sudoku::set_range(min_hole_num, max_hole_num);
		}
		if (opt_unique) {
			for (int i = 1; i <= game_num; i++) {
				Sudoku temp = Sudoku(false, true);
				temp.writeBoardToFile(file_names + std::to_string(i) + ".txt");
			}
		}
		else {
			for (int i = 1; i <= game_num; i++) {
				Sudoku temp = Sudoku(false);
				temp.writeBoardToFile(file_names + std::to_string(i) + ".txt");
			}
		}
	}
	return 0;
}