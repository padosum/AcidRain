/*
*
*		ver 0.1
*		yeonjeong choi
*/
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#define MAX_RAIN 100

#define SPEED 5

#define UP 72
#define DOWN 80
#define ENTER 13	

struct {
	int x, y;
	BOOL exist;
}RAIN[MAX_RAIN] = {0,};

int y = 10;
// 화살표의 위치 저장 
int menu = 0;

void gotoxy(int x, int y);
void DrawBoard();
void DrawMenu();
void MoveArrow(int key);
BOOL IsMenuSel();
BOOL IsKeyDown(int key);

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

BOOL IsKeyDown(int Key)
{
	return ((GetAsyncKeyState(Key) & 0x8000) != 0);
}

void DrawMenu()
{
	gotoxy(15, 4);
	printf("    _    ____ ___ ____    ____     _    ___ _   _ ");
	gotoxy(15, 5);
	printf("   / \\  / ___|_ _|  _ \\  |  _ \\   / \\  |_ _| \\ | |");
	gotoxy(15, 6);
	printf("  / _ \\| |    | || | | | | |_) | / _ \\  | ||  \\| |");
	gotoxy(15, 7);
	printf(" / ___ | |___ | || |_| | |  _ < / ___ \\ | || |\\  |");
	gotoxy(15, 8);
	printf("/_/   \\_\\____|___|____/  |_| \\_/_/   \\_|___|_| \\_|");
	gotoxy(27, 10);
	printf("▶	[게임 시작]");
	gotoxy(27, 12);
	printf("	[조작 설명]");
	gotoxy(27, 14);
	printf("	[만든이 정보]");
	gotoxy(27, 16);
	printf("	[게임 종료]");
}

void MoveArrow(int key)
{
	switch (key)
	{
	case UP:
		if (y > 10)
		{
			gotoxy(27, y);
			printf(" ");
			y -= 2;
			gotoxy(27, y);
			printf("▶");
		}
		break;

	case DOWN:
		if (y < 16)
		{
			gotoxy(27, y);
			printf(" ");
			y += 2;
			gotoxy(27, y);
			printf("▶");
		}
		break;

	case ENTER:
		if (y == 10)
		{
			system("cls");
			DrawBoard();
			IsMenuSel();
		}
		break;
	}
}

BOOL IsMenuSel()
{
	return menu = 1;
}

// 게임 판
void DrawBoard()
{
	int i;
	for (i = 0; i <= 40; i++)
	{
		gotoxy(i + 1, 0);
		printf("-");
		gotoxy(i + 1, 24);
		printf("-");
	}
	for (i = 0; i <= 22; i++)
	{
		gotoxy(1, i + 1);
		printf("|");
		gotoxy(41, i + 1);
		printf("|");
	}
}

int main()
{

	srand((int)time(NULL));
	int key;
	int score = 0;
	int life = 3;
	int px = 10;
	int count = 0;
	int i = 0;

	DrawMenu();

	while (menu == 0)
	{
		if (_kbhit())
		{
			key = _getch();
			MoveArrow(key);
		}
	}

	// 게임 시작 화면 
	gotoxy(15, 10);
	printf("TO START");
	gotoxy(15, 11);
	printf("PRESS ANY KEY");
	system("pause>>nul");

	gotoxy(15, 10);
	printf("                ");
	gotoxy(15, 11);
	printf("                      ");




	while (life > 0)
	{
		// score & life  
		gotoxy(45, 4);
		printf("Score: %d", score);
		gotoxy(45, 5);
		printf("Life: %d", life);

		// 비 생성
		if ((count % 10) == 1)
		{
			for (int i = 0; i <= MAX_RAIN; i++)
			{
				if (RAIN[i].exist == FALSE)
				{
					RAIN[i].exist = TRUE;
					RAIN[i].x = rand() % 37 + 3;
					RAIN[i].y = 1;
					break;
				}
			}
		}
		
		// 비의 이동
		if (count % SPEED == 1)
		{
			for (i = 0; i < MAX_RAIN; i++)
			{
				if (RAIN[i].exist == TRUE)
				{
					gotoxy(RAIN[i].x, RAIN[i].y);
					printf(" ");

					if (RAIN[i].y >= 23)
					{
						RAIN[i].exist = FALSE;
						score += 10;
						continue;
					}

					RAIN[i].y++;
					gotoxy(RAIN[i].x, RAIN[i].y);
					printf("|");
				}
			}
		}

		// 플레이어 이동
		if ((count % 5) == 1)
		{
			if (IsKeyDown(VK_LEFT))
			{
				if (px >= 3)
				{
					gotoxy(px, 23);
					putchar(' ');
					px--;
				}
			}
			else if (IsKeyDown(VK_RIGHT))
			{
				if (px < 39)
				{
					gotoxy(px, 23);
					putchar(' ');
					px++;
				}

			}
		}
		gotoxy(px, 23);
		printf("♀");

		if ((RAIN[i].x == px) && (RAIN[i].y == 23))
		{
			life--;
			RAIN[i].exist = FALSE;
		}

		count++;
		Sleep(10);
	}
		
}