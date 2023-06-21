#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <vector>
#include <algorithm>

#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <dirent.h>

using namespace std;

// 网格定义，固定大小为9×9
const int SIZE = 9;
char board[SIZE][SIZE]; // 全局变量默认初始化为0

bool check_path(const std::string &path)
{
    /*该函数尚未完成*/
    return 1;
}

bool is_valid(int row, int col, int num)
{
    /**
     * 检查在board[row][col]填入数值num是否合法
     */

    // 检查所在行和?列是否存在相同数字
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

bool fill_board(int row, int col)
{
    // 每行递归
    if (row == SIZE)
    {
        return true;
    }
    if (col == SIZE)
    {
        return fill_board(row + 1, 0);
    }
    if (board[row][col] != 0)
    {

        return fill_board(row, col + 1);
    }

    vector<int> nums;
    for (int num = 1; num <= SIZE; num++)
    {
        if (is_valid(row, col, num))
        {
            nums.push_back(num);
        }
    }
    random_shuffle(nums.begin(), nums.end());
    for (auto num : nums)
    {
        board[row][col] = num;
        cout << row << " " << col << " " << num << endl;
        if (fill_board(row, col + 1))
        {
            return true;
        }
    }
    board[row][col] = 0;
    return false;
}

void clear_board()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = 0;
        }
    }
}

void generate_final(int generate_num)
{
    // 打开文件
    ofstream fout("sudoku_final.txt");
    if (!fout)
    {
        cerr << "打开文件失败" << endl;
    }

    // 将数独终盘写入文件
    for (int i = 0; i < generate_num; i++)
    {
        srand(time(nullptr));

        // 生成数独终盘
        fill_board(0, 0);

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                fout << board[i][j] << " ";
            }
            fout << endl;
        }
        fout << endl;
    }
    fout.close();

    cout << "生成" << generate_num << "个数独终盘" << endl;
}

void generate_puzzle(int num, int min_holes_num, int max_holes_num)
{
    // 打开文件
    ofstream fout("sudoku_puzzle.txt");
    if (!fout)
    {
        cerr << "打开文件失败" << endl;
    }

    // 将数独终盘写入文件
    for (int i = 0; i < num; i++)
    {
        srand(time(nullptr));

        // 生成数独终盘
        fill_board(0, 0);

        // 随机生成挖洞数量
        int holes_num = rand() % (max_holes_num - min_holes_num + 1) + min_holes_num;

        // 记录已经挖去的洞的数量
        int count = 0;

        // 在游戏盘中随机挖取洞
        while (count < holes_num)
        {
            // 随机生成行、列索引
            int row = rand() % SIZE;
            int col = rand() % SIZE;

            // 如果该位置没有被挖掉，则将其挖掉，同时更新计数器
            if (board[row][col] != 0)
            {
                board[row][col] = 0;
                count++;
            }
        }

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (board[i][j] == 0)
                {
                    fout << "$  ";
                }
                else
                {
                    fout << board[i][j] << " ";
                }
            }
            fout << endl;
        }
        fout << endl;
    }
    fout.close();

    cout << "生成" << num << "个数独游戏" << endl;
}

int main(int argc, char *argv[])
{
    if (argc > 6)
    {
        cout << "传入参数多于2个！" << endl;
        return 0;
    }

    bool c_flag = false, s_flag = false, m_flag = false, n_flag = false, r_flag = false, u_flag = false;
    char *param_first, *param_second;
    int final_nums = 0, puzzle_nums = 0;
    int min_hole_nums = 0, max_hole_nums = 0;
    int diff = 1;

    for (int i = 1; i < argc; i += 2)
    {
        if (i == 1)
        {
            param_first = argv[i];
            if (!strcmp(param_first, "-c"))
            {
                final_nums = atoi(argv[i + 1]);
                if (final_nums > 1000000 || final_nums < 1)
                {
                    cout << "参数c范围不正确，应为1~1000000";
                    return 0;
                }
                if (argc > 3)
                {
                    cout << "使用-c后不能再使用其他参数！";
                    return 0;
                }
                c_flag = true;
            }
            else if (!strcmp(param_first, "-s"))
            {
                string path = argv[i + 1];
                if (!check_path(path))
                {
                    cout << "文件路径不正确" << endl;
                    return 0;
                }
                if (argc > 3)
                {
                    cout << "使用-s后不能再使用其他参数！";
                    return 0;
                }
                s_flag = true;
            }
            else if (!strcmp(param_first, "-n"))
            {
                puzzle_nums = atoi(argv[i + 1]);
                if (puzzle_nums > 10000 || puzzle_nums < 1)
                {
                    cout << "参数n范围不正确，应为1~10000";
                    return 0;
                }
                n_flag = true;
            }
            else
            {
                cout << "传入第一个参数有误！" << endl;
                return 0;
            }
        }
        else if (i == 3)
        {
            param_second = argv[i];
            if (!strcmp(param_second, "-u"))
            {
                if (argc != 4)
                {
                    cout << "使用参数u方法错误！" << endl;
                }
                u_flag = true;
            }
            else if (!strcmp(param_second, "-r"))
            {
                string range = argv[i + 1];
                pair<int, int> indices(-1, -1);

                // 查找分隔符 "~"
                size_t pos = range.find('~');
                if (pos != string::npos)
                {
                    // 分割字符串
                    string left_str = range.substr(0, pos);
                    string right_str = range.substr(pos + 1);

                    // 解析整数
                    int left_index = atoi(left_str.c_str());
                    int right_index = atoi(right_str.c_str());

                    // 检查下标合法性
                    if (left_index >= 0 && right_index >= left_index)
                    {
                        indices.first = left_index;
                        indices.second = right_index;
                    }
                }
                min_hole_nums = indices.first;
                max_hole_nums = indices.second;
                if (min_hole_nums < 0 || max_hole_nums > 64 || max_hole_nums > min_hole_nums)
                {
                    cout << "指定挖空数量不合规！" << endl;
                    return 0;
                }
                r_flag = true;
            }
            else if (!strcmp(param_second, "-m"))
            {
                diff = atoi(argv[i + 1]);
                if (diff < 1 || diff > 3)
                {
                    cout << "参数m范围不正确，应为1~3！" << endl;
                    return 0;
                }
                m_flag = true;
            }
            else
            {
                cout << "传入第二个参数有误！" << endl;
                return 0;
            }
        }
    }
}
