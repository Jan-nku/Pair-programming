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
/*����ȫ�ֱ����洢sudoku����*/

//-c��Ҫ��������������
bool opt_gen_final = false;
int final_num = 0;//���Ʒ�Χ��1-1000000

//-s��Ҫ������������ļ�·��
bool opt_solve = false;
char solve_file_path[256] = "";

//-n��Ҫ����Ϸ����
bool opt_number = false;
int game_num = 0;//������1-10000

//-m������Ϸ���Ѷ�<->�ڿ�����,��Ҫ��-nһͬʹ��
bool opt_level = false;
int game_level = 0;

//-r������Ϸ���ڿյ�������Χ����Ҫ��-nһͬʹ��
bool opt_range = false;
u_int min_hole_num = MIN_HOLE;
u_int max_hole_num = MAX_HOLE;

//-u����Ψһ�⣬��Ҫ��-nһͬʹ��
bool opt_unique = false;

void Assert(bool cond, std::string error = "") {
	if (!cond) {
		std::cout << error << std::endl;
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char* argv[]) {
	srand(time(nullptr));
	//part2:TODO
	/*option parser����getopt�⣬��������Ĳ����洢��������*/
	int opt;//optionѡ��
	char opt_arg[256];//�洢����
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
		Assert(final_num > 0, "��Ϸ�վ�������Ҫ > 0 !");
		Assert(final_num <= 1000000, "��Ϸ�վ�������Ҫ < 1000000 !");
	}
	if (opt_number) {
		Assert(game_num > 0, "��Ϸ������Ҫ > 0");
		Assert(game_num <= 10000, "��Ϸ������Ҫ < 10000");
	}
	if (opt_level) {
		Assert(opt_number, "opt-m ��Ҫopt-n");
		Assert((game_level == 1 || game_level == 2 || game_level == 3), "��Ϸ�ȼ�ȡֵΪ 1,2,3 !");
	}
	if (opt_range) {
		Assert(opt_number, "opt-r ��Ҫopt-n");
		Assert(min_hole_num <= max_hole_num, "�ڿ��������½����");
		Assert(MIN_HOLE <= min_hole_num, "�ڿ������½�С����Сֵ");
		Assert(MAX_HOLE >= max_hole_num, "�ڿ������½�������ֵ");
	}
	if (opt_unique) {
		Assert(opt_number, "opt-u ��Ҫopt-n");
	}

	//part4��TODO
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
		solveSudokuFile(solve_file_path);
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