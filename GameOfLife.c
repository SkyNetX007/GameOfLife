/*******************************************************************************************************************
** C����ģ��������Ϸ��Ԫ���Զ�����
**
** ĳһϸ�����ھӰ����ϡ��¡����ҡ����ϡ����¡���������������֮ϸ��
** ÿ��ϸ��������״̬:����������ÿ��ϸ����������Ϊ���ĵ���Χ�˸�ϸ������������
** ��ǰϸ��Ϊ���״̬ʱ������Χ����2����������2�������ϸ��ʱ�� ��ϸ���������״̬���µ�������ģ����������ϡ�٣�
** ��ǰϸ��Ϊ���״̬ʱ������Χ��2����3�����ϸ��ʱ�� ��ϸ������ԭ����״̬Ϊ�ȶ����
** ��ǰϸ��Ϊ���״̬ʱ������Χ��3�����ϵĴ��ϸ��ʱ����ϸ���������״̬��ӵ��������ģ�������������ࣩ
** ��ǰϸ��Ϊ����״̬ʱ������Χ��3�����ϸ��ʱ����ϸ����ɴ��״̬�� ��ģ�ֳⷱ��
** �ھӸ���Ϊ0��1��4��5��6��7��8ʱ�����ϸ���´�״̬Ϊ������
** �ھӸ���Ϊ2ʱ�����ϸ���´�״̬Ϊ���
** �ھӸ���Ϊ3ʱ�����ϸ���´�״̬Ϊ�ȶ���
*******************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#pragma comment(lib,"WINMM.LIB")

#define SIZE	32							//��ͼ����ĳ���
#define Death	printf("%c%c",0xA1,0xF5)	//��������
#define Live	printf("%c%c",0xA1,0xF6)	//����

boolean map_b[SIZE + 2][SIZE + 2] = { 0 };
int Gotoxy(int x, int y);
int Input();
void Initial(int map[SIZE + 2][SIZE + 2]);
void Display(const int map[SIZE + 2][SIZE + 2]);
void Transform(const int map[SIZE + 2][SIZE + 2]);
void RandMap(int map[SIZE + 2][SIZE + 2]);

void main()
{
	system("mode con cols=64 lines=34");
	system("title ������Ϸ (VERSION:1.0.0.0) by D.L.");
	system("color 8F");
	PlaySound("./data/BGM.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	Gotoxy(1, 1); printf("    ����������                               "); Gotoxy(1, 7); printf("    ����������          "); Gotoxy(1,13); printf("    ��                               ");
	Gotoxy(1, 2); printf("  ����            ______   _________   ______"); Gotoxy(1, 8); printf("  ����      ����  ______"); Gotoxy(1,14); printf("    ��          _____  ______  ______");
	Gotoxy(1, 3); printf("  ����  �������� | |  | | | | | | | \\ | |   "); Gotoxy(1, 9); printf("  ����      ���� | |    "); Gotoxy(1,15); printf("    ��           | |  | |     | |    ");
	Gotoxy(1, 4); printf("  ����      ���� | |__| | | | | | | | | |----"); Gotoxy(1,10); printf("  ����      ���� | |----"); Gotoxy(1,16); printf("    ��           | |  | |---- | |----");
	Gotoxy(1, 5); printf("    ����������   |_|  |_| |_| |_| |_| |_|____"); Gotoxy(1,11); printf("    ����������   |_|    "); Gotoxy(1,17); printf("    ����������  _|_|_ |_|     |_|____");
	Gotoxy(40, 8); printf("������Ϸ Game Of Life\n\n\n");
	Gotoxy(1, 20); printf("RULES:");
	Gotoxy(1, 22); printf("1)ĳһϸ�����ھӰ����ϡ��¡����ҡ����ϡ����¡���������������\n  ֮ϸ��");
	Gotoxy(1, 24); printf("2)ÿ��ϸ��������״̬:����������ÿ��ϸ����������Ϊ���ĵ���Χ��\n  ��ϸ����������");
	Gotoxy(1, 26); printf("3)��ǰϸ��Ϊ���״̬ʱ������Χ����2����������2�������ϸ��ʱ�� \n  ��ϸ���������״̬���µ�������ģ����������ϡ�٣�");
	Gotoxy(1, 28); printf("4)��ǰϸ��Ϊ���״̬ʱ������Χ��2����3�����ϸ��ʱ�� ��ϸ������\n  ԭ����״̬Ϊ�ȶ����");
	Gotoxy(1, 30); printf("5)��ǰϸ��Ϊ���״̬ʱ������Χ��3�����ϵĴ��ϸ��ʱ����ϸ�����\n  ����״̬��ӵ��������ģ�������������ࣩ");
	Gotoxy(1, 32); printf("6)��ǰϸ��Ϊ����״̬ʱ������Χ��3�����ϸ��ʱ����ϸ����ɴ��״\n  ̬��ģ�ֳⷱ��");

	int map[SIZE + 2][SIZE + 2] = { 0 };
	int *map_p = map;
	int count = 0;
	//map[4][4] = map[4][5] = map[4][6] = map[3][6] = map[2][5] = 1;

	Gotoxy(44, 12); printf("1���Զ����ͼ");
	Gotoxy(44, 14); printf("2���������");
	Gotoxy(44, 16); printf("3��Credits");
	Gotoxy(44, 18); printf("4���˳�");
	int Select = 1;
	while (1) {
		Sleep(100);
		int PlayerInput = Input();
		if (PlayerInput == 72 && Select > 1)
			Select--;
		if (PlayerInput == 80 && Select < 4)
			Select++;
		if (PlayerInput == 13)
			break;
		PlayerInput = 0;
		Gotoxy(40, 12); printf("   ");
		Gotoxy(40, 14); printf("   ");
		Gotoxy(40, 16); printf("   ");
		Gotoxy(40, 18); printf("   ");
		Gotoxy(40, 10 + 2 * Select);
		printf("-->");
	}
	switch (Select) {
	case 1:Initial(map_p); break;
	case 2:RandMap(map_p); break;
	case 3:system("cls");  Gotoxy(18, 16); printf("�� 4o4N0tF0und Studio ��Ʒ\n"); getchar(); main(); break;
	case 4:exit(0); break;
	}

	if (Select != 3)
	{
		while (1)
		{
			printf("                           ��%d��\n", count++);
			Display(map_p);
			Sleep(600);                           //���� 
			Transform(map_p);
			system("cls");                        //���� 
		}
	}
	
	system("pause");
}

/*�ƶ����*/
int Gotoxy(int x, int y)                          //��λ���λ��
{
	HANDLE handle;                                //����������handle
	COORD coord;                                  //����ṹ��coord (����ϵcoord)
	coord.X = x;                                  //������x
	coord.Y = y;                                  //������y
	handle = GetStdHandle(STD_OUTPUT_HANDLE);     //��ȡ����̨������(ֵΪ-11)
	SetConsoleCursorPosition(handle, coord);      //�ƶ����
}

int Input()
{
	int key = 0;
	while (_kbhit() != 0) {
		key = _getch();
		if (key != 0 && key != 224)
			return key;
	}
	return 0;
}

/*�û���ʼ��*/
void Initial(int map[SIZE + 2][SIZE + 2])
{
	int x = 0, y = 0;
	int blockCNT = 0;
	printf("���������");
	scanf_s("%d", &blockCNT);
	system("cls");
	
	for (int i = 0; i < blockCNT; i++)
	{
		Display(map);
		printf("����������꣬��ʽ��x y��������ȡֵ��1 - %d����", SIZE);
		scanf_s("%d %d", &x, &y);
		map[x][y] = 1;
	}
}

/*�ı�״̬*/
void Transform(int map[SIZE + 2][SIZE + 2])
{
	int w, h, sum;
	sum = 0;
	int map_t[SIZE + 2][SIZE + 2] = { 0 };

	for (w = 1; w <= SIZE; w++)
		for (h = 1; h <= SIZE; h++)
			map_t[w][h] = map[w][h];

	for (w = 1; w <= SIZE; w++) {

		for (h = 1; h <= SIZE; h++) {

			sum = map_t[w - 1][h - 1] + map_t[w - 1][h] + map_t[w - 1][h + 1]
				+ map_t[w][h - 1] + map_t[w][h + 1]
				+ map_t[w + 1][h - 1] + map_t[w + 1][h] + map_t[w + 1][h + 1];

			switch (sum)
			{
			case 2:
				break;
			case 3:
				if (map_t[w][h] == 0)
					map[w][h] = 1;
				break;
			default:
				map[w][h] = 0;
				break;

			}
		}
	}
}


/*��ʾ*/
void Display(const int map[SIZE + 2][SIZE + 2]) {

	int w, h;

	for (w = 1; w <= SIZE; w++) {
		for (h = 1; h <= SIZE; h++) {
			if (map[w][h] == 1)
				Live;
			else
				Death;
		}
		printf("\n");
	}
}

/*�����ͼ*/
void RandMap(int map[SIZE + 2][SIZE + 2])
{
	system("cls");
	srand((unsigned)time(NULL));
	for (int x = 1; x < SIZE; x++)
	{
		for (int y = 1; y < SIZE; y++)
		{
		map[x][y] = rand() % 2;
		}
	}
}