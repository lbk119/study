#define _CRT_SECURE_NO_WARNINGS
//扫雷游戏
#include "game.h"
int main()
{
	int input;
	//在main函数确定种子
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("游戏开始\n");
			game();
			break;
		case 2:
			printf("退出游戏\n");
			break;
		default:
			printf("输入错误，请重新选择\n");
			break;
		}
	} while (input != 2);
	return 0;
}