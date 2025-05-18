#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROW 9
#define COL 9
#define ROWS ROW+2
#define COLS COL+2
#define MineCount 10
void menu();
void game();
void InitBoard(char arr[ROWS][COLS], int rows,
	int cols, char set);
void Setmine(char arr[ROWS][COLS], int row, int col);
void FindMine(char board[ROWS][COLS], char show[ROWS][COLS]
	, int row, int col);
int SuroundCount(char arr[ROWS][COLS], int x, int y);
