#define _CRT_SECURE_NO_WARNINGS
//ɨ����Ϸ
#include "game.h"
int main()
{
	int input;
	//��main����ȷ������
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("��Ϸ��ʼ\n");
			game();
			break;
		case 2:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("�������������ѡ��\n");
			break;
		}
	} while (input != 2);
	return 0;
}