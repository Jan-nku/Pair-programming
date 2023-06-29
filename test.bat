@echo off
cd /d "D:\2023_Spring\sudoku\Debug"

echo off > output.txt

REM 测试参数-c
echo "test arg -c,value:10,0,1000001" >> output.txt 2>&1

echo "[Command 1] sudoku.exe -c 10" >> output.txt
sudoku.exe -c 10 >> output.txt 2>&1
echo. >> output.txt

echo "[Command 2] sudoku.exe -c 0" >> output.txt
sudoku.exe -c 0 >> output.txt 2>&1
echo. >> output.txt

echo "[Command 3] sudoku.exe -c 1000001 completed." >> output.txt
sudoku.exe -c 1000001 >> output.txt 2>&1
echo. >> output.txt


REM 测试参数-n
echo. >> output.txt
echo "test arg -n, value:10,0,10001" >> output.txt 2>&1
echo "[Command 4] sudoku.exe -n 10" >> output.txt
sudoku.exe -n 10 >> output.txt 2>&1
echo. >> output.txt

echo "[Command 5] sudoku.exe -n 0" >> output.txt
sudoku.exe -n 0 >> output.txt 2>&1
echo. >> output.txt

echo "[Command 6] sudoku.exe -c 10001 completed." >> output.txt
sudoku.exe -n 10001 >> output.txt 2>&1
echo. >> output.txt


REM 测试参数-m
echo. >> output.txt
echo "test arg -m, value:no arg -n,0,1,4" >> output.txt 2>&1
echo "[Command 7] sudoku.exe -m 1 " >> output.txt
sudoku.exe -m 1 >> output.txt 2>&1
echo. >> output.txt

echo "[Command 8] sudoku.exe -n 10 -m 0" >> output.txt
sudoku.exe -n 10 -m 0 >> output.txt 2>&1
echo. >> output.txt

echo "[Command 9] sudoku.exe -n 10 -m 1" >> output.txt
sudoku.exe -n 10 -m 1 >> output.txt 2>&1
echo. >> output.txt

echo "[Command 10] sudoku.exe -n 10 -m 4" >> output.txt
sudoku.exe -n 10 -m 4 >> output.txt 2>&1
echo. >> output.txt


REM 测试参数-r
echo. >> output.txt
echo "test arg -r, value:no arg -n,-1~30,20~40,30~61,40~30" >> output.txt 2>&1
echo "[Command 11] sudoku.exe -r 30~40" >> output.txt
sudoku.exe -r 30~40 >> output.txt 2>&1
echo. >> output.txt

echo "[Command 12] sudoku.exe -n 10 -r -1~30" >> output.txt
sudoku.exe -n 10 -r -1~30  >> output.txt 2>&1
echo. >> output.txt

echo "[Command 13] sudoku.exe -n 10 -r 20~40" >> output.txt
sudoku.exe -n 10 -r 20~40  >> output.txt 2>&1
echo. >> output.txt

echo "[Command 14] sudoku.exe -n 10 -r 30~61" >> output.txt
sudoku.exe -n 10 -r 30~61  >> output.txt 2>&1
echo. >> output.txt

echo "[Command 15] sudoku.exe -n 10 -r 40~30" >> output.txt
sudoku.exe -n 10 -r 40~30  >> output.txt 2>&1
echo. >> output.txt

REM 测试参数-u
echo. >> output.txt
echo "test arg -u, value:no arg -n" >> output.txt 2>&1
echo "[Command 16] sudoku.exe -u" >> output.txt
sudoku.exe -u >> output.txt 2>&1
echo. >> output.txt

echo "[Command 17] sudoku.exe -n 10 -u" >> output.txt
sudoku.exe -n 10 -u  >> output.txt 2>&1
echo. >> output.txt

REM 测试参数-s
echo. >> output.txt
echo "test arg -s, value:path error,relative path,absolute path" >> output.txt 2>&1
echo "[Command 18] sudoku.exe -s "./error/game_1" " >> output.txt
sudoku.exe -s "./error/game_1" >> output.txt 2>&1
echo. >> output.txt

echo "[Command 19] sudoku.exe -s "./games/game_1.txt"" >> output.txt
sudoku.exe -s "./games/game_1.txt"  >> output.txt 2>&1
echo. >> output.txt

echo "[Command 20] sudoku.exe -s "D:\2023_Spring\sudoku/Debug/games/game_1.txt"" >> output.txt
sudoku.exe -s "D:\2023_Spring\sudoku/Debug/games/game_1.txt"  >> output.txt 2>&1
echo. >> output.txt