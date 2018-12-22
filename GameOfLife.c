/*******************************************************************************************************************
** C语言模拟生命游戏（元胞自动机）
**
** 某一细胞的邻居包括上、下、左、右、左上、左下、右上与右下相邻之细胞
** 每个细胞有两种状态:存活或死亡，每个细胞与以自身为中心的周围八格细胞产生互动。
** 当前细胞为存活状态时，当周围低于2个（不包含2个）存活细胞时， 该细胞变成死亡状态。孤单死亡（模拟生命数量稀少）
** 当前细胞为存活状态时，当周围有2个或3个存活细胞时， 该细胞保持原样。状态为稳定存活
** 当前细胞为存活状态时，当周围有3个以上的存活细胞时，该细胞变成死亡状态。拥挤死亡（模拟生命数量过多）
** 当前细胞为死亡状态时，当周围有3个存活细胞时，该细胞变成存活状态。 （模拟繁殖）
** 邻居个数为0、1、4、5、6、7、8时，则该细胞下次状态为死亡。
** 邻居个数为2时，则该细胞下次状态为复活。
** 邻居个数为3时，则该细胞下次状态为稳定。
*******************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#pragma comment(lib,"WINMM.LIB")

#define SIZE	32							//地图数组的长度
#define Death	printf("%c%c",0xA1,0xF5)	//死亡方块
#define Live	printf("%c%c",0xA1,0xF6)	//存活方块

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
	system("title 生命游戏 (VERSION:1.0.0.0) by D.L.");
	system("color 8F");
	PlaySound("./data/BGM.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	Gotoxy(1, 1); printf("    █████                               "); Gotoxy(1, 7); printf("    █████          "); Gotoxy(1,13); printf("    █                               ");
	Gotoxy(1, 2); printf("  ██            ______   _________   ______"); Gotoxy(1, 8); printf("  ██      ██  ______"); Gotoxy(1,14); printf("    █          _____  ______  ______");
	Gotoxy(1, 3); printf("  ██  ████ | |  | | | | | | | \\ | |   "); Gotoxy(1, 9); printf("  ██      ██ | |    "); Gotoxy(1,15); printf("    █           | |  | |     | |    ");
	Gotoxy(1, 4); printf("  ██      ██ | |__| | | | | | | | | |----"); Gotoxy(1,10); printf("  ██      ██ | |----"); Gotoxy(1,16); printf("    █           | |  | |---- | |----");
	Gotoxy(1, 5); printf("    █████   |_|  |_| |_| |_| |_| |_|____"); Gotoxy(1,11); printf("    █████   |_|    "); Gotoxy(1,17); printf("    █████  _|_|_ |_|     |_|____");
	Gotoxy(40, 8); printf("生命游戏 Game Of Life\n\n\n");
	Gotoxy(1, 20); printf("RULES:");
	Gotoxy(1, 22); printf("1)某一细胞的邻居包括上、下、左、右、左上、左下、右上与右下相邻\n  之细胞");
	Gotoxy(1, 24); printf("2)每个细胞有两种状态:存活或死亡，每个细胞与以自身为中心的周围八\n  格细胞产生互动");
	Gotoxy(1, 26); printf("3)当前细胞为存活状态时，当周围低于2个（不包含2个）存活细胞时， \n  该细胞变成死亡状态。孤单死亡（模拟生命数量稀少）");
	Gotoxy(1, 28); printf("4)当前细胞为存活状态时，当周围有2个或3个存活细胞时， 该细胞保持\n  原样。状态为稳定存活");
	Gotoxy(1, 30); printf("5)当前细胞为存活状态时，当周围有3个以上的存活细胞时，该细胞变成\n  死亡状态。拥挤死亡（模拟生命数量过多）");
	Gotoxy(1, 32); printf("6)当前细胞为死亡状态时，当周围有3个存活细胞时，该细胞变成存活状\n  态（模拟繁殖）");

	int map[SIZE + 2][SIZE + 2] = { 0 };
	int *map_p = map;
	int count = 0;
	//map[4][4] = map[4][5] = map[4][6] = map[3][6] = map[2][5] = 1;

	Gotoxy(44, 12); printf("1）自定义地图");
	Gotoxy(44, 14); printf("2）随机生成");
	Gotoxy(44, 16); printf("3）Credits");
	Gotoxy(44, 18); printf("4）退出");
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
	case 3:system("cls");  Gotoxy(18, 16); printf("由 4o4N0tF0und Studio 出品\n"); getchar(); main(); break;
	case 4:exit(0); break;
	}

	if (Select != 3)
	{
		while (1)
		{
			printf("                           第%d代\n", count++);
			Display(map_p);
			Sleep(600);                           //休眠 
			Transform(map_p);
			system("cls");                        //清屏 
		}
	}
	
	system("pause");
}

/*移动光标*/
int Gotoxy(int x, int y)                          //定位光标位置
{
	HANDLE handle;                                //定义句柄变量handle
	COORD coord;                                  //定义结构体coord (坐标系coord)
	coord.X = x;                                  //横坐标x
	coord.Y = y;                                  //纵坐标y
	handle = GetStdHandle(STD_OUTPUT_HANDLE);     //获取控制台输出句柄(值为-11)
	SetConsoleCursorPosition(handle, coord);      //移动光标
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

/*用户初始化*/
void Initial(int map[SIZE + 2][SIZE + 2])
{
	int x = 0, y = 0;
	int blockCNT = 0;
	printf("存活方块个数：");
	scanf_s("%d", &blockCNT);
	system("cls");
	
	for (int i = 0; i < blockCNT; i++)
	{
		Display(map);
		printf("输入存活方块坐标，格式“x y”（坐标取值：1 - %d）：", SIZE);
		scanf_s("%d %d", &x, &y);
		map[x][y] = 1;
	}
}

/*改变状态*/
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


/*显示*/
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

/*随机地图*/
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