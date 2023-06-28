#include<iostream>
#include<fstream>
#include"sudokuSolve.h"


//Part6£ºTODO
//solveSudokuFile function import the sudoku board from the inputFilePath, and write the solved board to outputFilePath 
void solveSudokuFile(const std::string inputFilePath, const std::string outputFilePath) {
    //open the input file and the output file
    std::ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input file: " << inputFilePath << std::endl;
        return;
    }
    std::ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file: " << outputFilePath << std::endl;
        inputFile.close();
        return;
    }
    SudokuSolve sudokuSolve;
    //Read several sudoku games from inputFilePath, give their solutions, and generate in outputFilePath
    while (!inputFile.eof()) {
        //define the interface to complete: readFromFile¡¢solve¡¢writeToFile
        sudokuSolve.readFromFile(inputFile);
        if (sudokuSolve.solve()) {
            sudokuSolve.writeToFile(outputFile);
        }
        else {
            outputFile << "The soduko Board has no solutions!\n";
        }
    }

    inputFile.close();
    outputFile.close();
    return;
}


