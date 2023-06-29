#include <iostream>
#include <fstream>
#include "sudokuSolve.h"
#include "sudoku.h"
#include <vector>

bool SudokuSolve::solveSudoku()
{
    for (int row = 0; row < SIZE; ++row)
    {
        for (int col = 0; col < SIZE; ++col)
        {
            if (sudoku.board[row][col] == -1)
            {
                for (int num = 1; num <= SIZE; ++num)
                {
                    if (this->sudoku.isValid(row, col, num))
                    {
                        sudoku.board[row][col] = num;
                        if (solveSudoku())
                        {
                            return true;
                        }
                        sudoku.board[row][col] = -1;
                    }
                }
                return false;
            }
        }
    }
    return true; // 数独已经全部填充完成
}

// Part6: TODO
// solveSudokuFile function import the sudoku board from the inputFilePath, and write the solved board to outputFilePath
void SudokuSolve::solveSudokuFile(const std::string& inputFilePath, const std::string& outputFilePath)
{
    // open the input file and the output file
    std::ifstream inputFile(inputFilePath);
    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open input file: " << inputFilePath << std::endl;
        return;
    }
    std::ofstream outputFile(outputFilePath);
    if (!outputFile.is_open())
    {
        std::cerr << "Failed to open output file: " << outputFilePath << std::endl;
        inputFile.close();
        return;
    }
    SudokuSolve sudokuSolve;
    // Read several sudoku games from inputFilePath, give their solutions, and generate in outputFilePath
    while (!inputFile.eof())
    {
        sudokuSolve.readFromFile(inputFile);
        if (sudokuSolve.solveSudoku())
        {
            sudokuSolve.writeToFile(outputFile);  
        }
        else
        {
            outputFile << "The soduko Board has no solutions!\n";
        }
    }

    inputFile.close();
    outputFile.close();
    return;
}

void SudokuSolve::readFromFile(std::ifstream& file)
{
    std::string line;
    int row = 0;
    while (std::getline(file, line)) {
        if (line.empty()) {
            break;
        }
        for (int col = 0; col < SIZE; col++) {
            char c = line[col * 2];
            if (c == '$') {
                sudoku.board[row][col] = -1;
            }
            else {
                sudoku.board[row][col] = c - '0';
            }
        }
        row++;
    }
}

void SudokuSolve::writeToFile(std::ofstream& file) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            file << sudoku.board[i][j] << " ";
        }
        file << std::endl;
    }
    file << std::endl;
}