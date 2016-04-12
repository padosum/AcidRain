/***
*     ________  ________  ___  ________          ________  ________  ___  ________
*    |\   __  \|\   ____\|\  \|\   ___ \        |\   __  \|\   __  \|\  \|\   ___  \
*    \ \  \|\  \ \  \___|\ \  \ \  \_|\ \       \ \  \|\  \ \  \|\  \ \  \ \  \\ \  \
*     \ \   __  \ \  \    \ \  \ \  \ \\ \       \ \   _  _\ \   __  \ \  \ \  \\ \  \
*      \ \  \ \  \ \  \____\ \  \ \  \_\\ \       \ \  \\  \\ \  \ \  \ \  \ \  \\ \  \
*       \ \__\ \__\ \_______\ \__\ \_______\       \ \__\\ _\\ \__\ \__\ \__\ \__\\ \__\
*        \|__|\|__|\|_______|\|__|\|_______|        \|__|\|__|\|__|\|__|\|__|\|__| \|__|
*
*		ver 0.1
*		yeonjeong choi
*/
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#define UP 72
#define DOWN 80
#define ENTER 13

int y = 10;
// 화살표의 위치 저장

void gotoxy(int x, int y, char str[]);
void DrawBoard();
void DrawMenu();
void MoveArrow(int key);

void gotoxy(int x, int y, char str[])
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
	printf("%s", str);
}

void DrawMenu()
{
	gotoxy(15, 4, "    _    ____ ___ ____    ____     _    ___ _   _ ");
	gotoxy(15, 5, "   / \\  / ___|_ _|  _ \\  |  _ \\   / \\  |_ _| \\ | |");
	gotoxy(15, 6, "  / _ \\| |    | || | | | | |_) | / _ \\  | ||  \\| |");
	gotoxy(15, 7, " / ___ | |___ | || |_| | |  _ < / ___ \\ | || |\\  |");
	gotoxy(15, 8, "/_/   \\_\\____|___|____/  |_| \\_/_/   \\_|___|_| \\_|");
	gotoxy(27, 10, "▶	[게임 시작]");
	gotoxy(27, 12, "	[조작 설명]");
	gotoxy(27, 14, "	[만든이 정보]");
	gotoxy(27, 16, "	[게임 종료]");
}

void MoveArrow(int key)
{
	switch (key)
	{
	case UP:
		if (y > 10)
		{
			gotoxy(27, y, " ");
			y -= 2;
			gotoxy(27, y, "▶");
		}
		break;

	case DOWN:
		if (y < 16)
		{
			gotoxy(27, y, " ");
			y += 2;
			gotoxy(27, y, "▶");
		}
		break;

	case ENTER:
		if (y == 10)
		{
			system("cls");
			DrawBoard();
		}
		break;
	}
}

void DrawBoard()
{
	int i;
	for (i = 0; i <= 20; i++)
	{
		gotoxy(i + 1, 0, "-");
		gotoxy(i + 1, 24, "-");
	}
	for (i = 0; i <= 22; i++)
	{
		gotoxy(1, i + 1, "|");
		gotoxy(21, i + 1, "|");
	}
}
int main()
{
	int key;

	DrawMenu();

	while (1)
	{
		if (_kbhit())
		{
			key = _getch();
			MoveArrow(key);
		}
	}
}
