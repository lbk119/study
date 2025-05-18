#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 
#include "game.h"
void menu()
{
	printf("*****************\n");
	printf("*****1. play*****\n");
	printf("*****2. exit*****\n");
	printf("*****************\n");
	printf("��ѡ��\n");
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
	//Ϊ��֤�����������׵Ŀɶ��ԣ���������ϵ
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
	//����ȡ���к��еķ�Χ
	int i = 0;
	while (i < MineCount)
	{
		int x = rand() % row + 1, y = rand() % col + 1;
		//��֤���õ��ײ��ظ�
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
		printf("������Ҫ�ų�������\n");
		int x, y;
		scanf("%d%d", &x, &y);
		if ((x >= 1 && x <= row) && (y >= 1 && y <= col))
		{
			if (board[x][y] == '1')
			{
				printf("�ǳ���Ǹ���㱻��ը����\n");
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
			printf("�����������\n");
		}
		system("cls");//������Ļ
		Display(show, ROW, COL);
	}
	if (win == MineCount)
		printf("��ϲ�����׳ɹ�\n");

}

void game()
{
	//1.��ʼ������
	//ʵ�������к��д�С����Ҫ�к��д�С��2����ֹ����Խ��
	//��ʼ���������飬һ����ӡ����Ļ�ϣ���*��
	// һ�����׺����ף��á�1����ʾ�ף���0����ʾ����
//
	char board[ROWS][COLS], show[ROWS][COLS];
	InitBoard(board, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');
	//2.��ӡ����
	//Display(board,ROW,COL);
	Display(show, ROW, COL);
	//3����.
	Setmine(board, ROW, COL);
	Display(board, ROW, COL);
	//4.����
	FindMine(board, show, ROW, COL);
}