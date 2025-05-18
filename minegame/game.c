#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 
#include "game.h"
void menu()
{
	printf("*****************\n");
	printf("*****1. play*****\n");
	printf("*****2. exit*****\n");
	printf("*****************\n");
	printf("请选择\n");
}
void InitBoard(char arr[ROWS][COLS], int rows, int cols, char set)
{
	int i = 0;
	for (i = 0; i < rows; i++)
	{
		int j = 0;
		for (j = 0; j < cols; j++)
		{
			arr[i][j] = set;
		}
	}
}
void Display(char arr[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	//为保证输入坐标排雷的可读性，建立坐标系
	for (j = 0; j <= col; j++)
		printf("%d ", j);
	printf("\n");
	for (i = 1; i <= row; i++)
	{

		for (j = 1; j <= col; j++)
		{
			if (j == 1)
			{
				printf("%d ", i);
			}
			printf("%c ", arr[i][j]);
		}
		printf("\n");
	}

}
void Setmine(char arr[ROWS][COLS], int row, int col)
{
	//坐标取到行和列的范围
	int i = 0;
	while (i < MineCount)
	{
		int x = rand() % row + 1, y = rand() % col + 1;
		//保证设置的雷不重复
		if (arr[x][y] == '0')
		{
			arr[x][y] = '1';
			i++;
		}
	}
}
int SuroundCount(char arr[ROWS][COLS], int x, int y)
{
	int i = 0,j=0,count=0;
	for (i = x - 1; i <= x + 1; i++)
	{
		for (j = y - 1; j<= y + 1; j++)
		{
			if (arr[i][j] == '1')
			{
				count++;
			}
		}
	}
	return count;
}
void FindMine(char board[ROWS][COLS], char show[ROWS][COLS]
	, int row, int col)
{
	int win = 0;
	while (win < MineCount)
	{
		printf("请输入要排除的坐标\n");
		int x, y;
		scanf("%d%d", &x, &y);
		if ((x >= 1 && x <= row) && (y >= 1 && y <= col))
		{
			if (board[x][y] == '1')
			{
				printf("非常抱歉，你被雷炸死了\n");
				Display(board, ROW, COL);
				break;
			}
			else if (board[x][y] == '0')
			{
				int count = SuroundCount(board, x, y);
				show[x][y] = '0'+count;
				win++;
			}
		}
		else
		{
			printf("坐标输入错误\n");
		}
		system("cls");//清理屏幕
		Display(show, ROW, COL);
	}
	if (win == MineCount)
		printf("恭喜你排雷成功\n");

}

void game()
{
	//1.初始化棋盘
	//实际数组行和列大小比需要行和列大小大2，防止访问越界
	//初始化两个数组，一个打印在屏幕上，用*，
	// 一个埋雷和排雷，用‘1’表示雷，‘0’表示非雷
//
	char board[ROWS][COLS], show[ROWS][COLS];
	InitBoard(board, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');
	//2.打印棋盘
	//Display(board,ROW,COL);
	Display(show, ROW, COL);
	//3埋雷.
	Setmine(board, ROW, COL);
	Display(board, ROW, COL);
	//4.排雷
	FindMine(board, show, ROW, COL);
}