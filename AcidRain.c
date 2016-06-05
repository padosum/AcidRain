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

#define WIDTH 20
#define HEIGHT 23


typedef struct object{
	int x, y;
	int exist;
} Object;

Object rain[MAX_RAIN];
Object player;

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

	// 가로
	for (i = 0; i < WIDTH; i++)
		printf("▧");
	gotoxy(0, HEIGHT);
	for (i = 0; i < WIDTH+1; i++)
		printf("▧");

	// 세로
	for (i = 0; i < HEIGHT; i++)
	{
		gotoxy(0, i);
		printf("▧");
	}
	for (i = 0; i < HEIGHT; i++)
	{
		gotoxy(WIDTH*2, i);
		printf("▧");
	}

}

// 초기화
void Init()
{
	int i;

	for (i = 0; i < MAX_RAIN; i++)
		rain[i].exist = FALSE;

	player.x = WIDTH;
}

void MovePlayer()
{
	// 플레이어 이동
	if (IsKeyDown(VK_LEFT))
	{
		if (player.x >= 3)
		{
			gotoxy(player.x, 22);
			putchar(' ');
			player.x--;
		}
	}
	else if (IsKeyDown(VK_RIGHT))
	{
		if (player.x < 38)
		{
			gotoxy(player.x, 22);
			putchar(' ');
			player.x++;
		}

	}
	gotoxy(player.x, 22);
	printf("♀");
}

void CreateRain()
{
	// 비 생성
	for (int i = 0; i <= MAX_RAIN; i++)
	{
		if (rain[i].exist == FALSE)
		{
			rain[i].exist = TRUE;

			rain[i].x = rand() % 37 + 2;
			rain[i].y = 1;

			return;
		}
	}

}

int MoveRain()
{
	// 비의 이동
	int i;
	int score = 0;
	int life = 3;

	for (i = 0; i < MAX_RAIN; i++)
	{
		if (rain[i].exist == TRUE)
		{
			gotoxy(rain[i].x, rain[i].y);
			printf(" ");

			if (rain[i].y == HEIGHT-1)
			{
				rain[i].exist = FALSE;
				score += 10;
				continue;

				if (rain[i].x && player.x)
				{
					life--;
				}
			}
			rain[i].y++;
			gotoxy(rain[i].x, rain[i].y);
			printf("|");
		}

		// score & life  
		gotoxy(45, 4);
		printf("Score: %d", score);
		gotoxy(45, 5);
		printf("Life: %d", life);
	}

}


int main()
{

	srand((int)time(NULL));
	int key;
	int i = 0;
	int score = 0;
	int life = 3;

	Init();
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




	while(1)
	{

		MovePlayer();
		CreateRain();
		MoveRain();
	
		Sleep(50);
	} 
		
}