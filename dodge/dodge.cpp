#pragma warning(disable:4996)
#include  <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <vector>

#define ONE_SECOND 1000

using namespace std;

typedef struct Enemy {
	int x;
	int y;
	int direct;
}Enemy;
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main()
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = false;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
	system("mode con: cols=130 lines=40");
	srand(time(NULL));
	int x = 10;
	int y = 13;
	char szChoice = 0;
	// 129 34
	vector<Enemy> enemyList;
	for (int i = 0; i < 10; i++)
	{
		Enemy enemy;
		enemy.x = rand() % 130;
		enemy.y = rand() % 35;
		enemy.direct = rand() % 6;
		enemyList.push_back(enemy);
	}

	gotoxy(x, y);
	printf("@");
	unsigned __int64 prevTime = GetTickCount();
	unsigned __int64 createTime = GetTickCount();
	for (auto e : enemyList)
	{
		gotoxy(e.x, e.y);
		printf("o");
	}
	clock_t start = clock();
	bool canPlay = true;
	while (canPlay)
	{
		if (kbhit())
		{
			int tempX = x;
			int tempY = y;
			szChoice = getch();
			switch (szChoice)
			{
			case 'w':
				tempY--;
				break;
			case 'a':
				tempX--;
				break;
			case 's':
				tempY++;
				break;
			case 'd':
				tempX++;
				break;
			}
			if (tempX >= 0 && tempY >= 0 && tempX < 130 && tempY < 35)
			{
				gotoxy(x, y);
				printf(" ");
				gotoxy(tempX, tempY);
				printf("@");
				x = tempX;
				y = tempY;
			}
		

		}

		unsigned __int64 curTime = GetTickCount();
		if (curTime - prevTime > 50)	//0.05초마다
		{
			for (int i = 0; i < enemyList.size(); i++)
			{
				gotoxy(enemyList[i].x, enemyList[i].y);
				printf(" ");

				if (enemyList[i].x == 129 && enemyList[i].direct == 0)//오른쪽 가로로 가는 방향
					enemyList[i].x = 0;
				if (enemyList[i].y == 34 && enemyList[i].direct == 3)//아래로 가는 방향
					enemyList[i].y = 0;
				if (enemyList[i].x == 0 && enemyList[i].direct == 1)//왼쪽 가로로 가는 방향
					enemyList[i].x = 129;
				if (enemyList[i].y == 0 && enemyList[i].direct == 2)//위로 가는 방향
					enemyList[i].y = 34;
				if (enemyList[i].direct == 4)	 //오른쪽 대각선 아래
				{
					if (enemyList[i].y == 34)
						enemyList[i].y = 0;
					if (enemyList[i].x == 129)
						enemyList[i].x = 0;
				}
				if (enemyList[i].direct == 5)	 //오른쪽 대각선 아래
				{
					if (enemyList[i].y == 34)
						enemyList[i].y = 0;
					if (enemyList[i].x == 0)
						enemyList[i].x = 129;
				}


				if (enemyList[i].direct == 0)
					enemyList[i].x++;
				else if (enemyList[i].direct == 1)
					enemyList[i].x--;
				else if (enemyList[i].direct == 2)
					enemyList[i].y--;
				else if (enemyList[i].direct == 3)
					enemyList[i].y++;
				else if (enemyList[i].direct == 4)
				{
					enemyList[i].y++;
					enemyList[i].x++;
				}
					else if (enemyList[i].direct == 5)
					{
						enemyList[i].y++;
						enemyList[i].x--;
					}

				gotoxy(enemyList[i].x, enemyList[i].y);
				printf("o");

				if (enemyList[i].x == x && enemyList[i].y == y)
				{
					canPlay = false;
					break;
				}
			}

			prevTime = curTime;
		}
		
		if (curTime - createTime > 500)
		{
			Enemy enemy;
			while (1)
			{

				enemy.x = rand() % 130;
				enemy.y = rand() % 35;

				if ((enemy.x - x) * (enemy.x - x) + (enemy.y - y) * (enemy.y - y) > 25)
					break;
			}
			enemy.direct = rand() % 6;
			enemyList.push_back(enemy);
			createTime = curTime;
		}
		
		

		clock_t end = clock();
		double time = double(end - start) / CLOCKS_PER_SEC; //초단위 변환
		gotoxy(10, 37);
		printf("경과시간 : %0.3lf\n", time); //소수점 셋째 자리까지
	}



	return 0;
}

