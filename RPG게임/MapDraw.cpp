#include "MapDraw.h"


MapDraw::MapDraw()
{

}

void MapDraw::ErasePoint(int x, int y)
{
	gotoxy(x * 2, y);
	cout << " ";
	return;
}
void MapDraw::DrawPoint(string str, int x, int y)
{
	gotoxy(x * 2, y);
	cout << str;
	gotoxy(-1, -1);
	return;
}

void MapDraw::DrawMidText(string str, int x, int y)
{
	if (x > str.size() / 2)
		x -= str.size() / 2;
	gotoxy(x, y);
	cout << str;
	return;
}
void MapDraw::TextDraw(string str, int x, int y)
{
	gotoxy(x, y);
	cout << str;
}


void MapDraw::BoxErase(int Width, int Height)
{
	for (int y = 1; y < Height - 1; y++)
	{
		gotoxy(2, y);
		for (int x = 1; x < Width - 1; x++)
			cout << "  ";
	}
}

void MapDraw::BoxDraw(int Start_x, int Start_y, int Width, int Height)
{
	BLUE
	if (Start_x > Width)
		Start_x -= Width;
	for (int y = 0; y < Height; y++)
	{
		gotoxy(Start_x, Start_y + y);
		if (y == 0)
		{
			cout << "┌";
			for (int x = 1; x < Width - 1; x++)

				cout << "─";
			cout << "┐";
		}
		else if (y == Height - 1)
		{
			cout << "└";
			for (int x = 1; x < Width - 1; x++)
				cout << "─";
			cout << "┘";
		}
		else
		{
			cout << "│";
			for (int x = 1; x < Width - 1; x++)
				cout << "  ";
			cout << "│";
		}
	}
	ORIGINAL
	return;
}

int MapDraw::MenuSelectCursor(int MenuLen, int AddCol, int x, int y)
{
	int Select = 1;
	RED
		DrawPoint("▷", x, y);
	ORIGINAL
		while (1)
		{
			switch (getch())
			{
			case UP:
				if (Select - 1 >= 1)
				{
					ErasePoint(x, y);
					y -= AddCol;
					Select--;
				}
				break;
			case DOWN:
				if (Select + 1 <= MenuLen)
				{
					ErasePoint(x, y);
					y += AddCol;
					Select++;
				}
				break;
			case ENTER:
				return Select;
			}
			RED
				DrawPoint("▷", x, y);
			ORIGINAL
		}
}

void MapDraw::FirstMenu()
{
	DrawMidText("☆★ DonGeon RPG ★☆", WIDTH, HEIGHT * 0.4);
	DrawMidText("New Game", WIDTH, HEIGHT * 0.5);
	DrawMidText("Load Game", WIDTH, HEIGHT * 0.6);
	DrawMidText("Game Exit", WIDTH, HEIGHT * 0.7);
}

void MapDraw::GameMenu()
{
	DrawMidText("☆★ Menu ★☆", WIDTH, HEIGHT * 0.25 + 2);
	DrawMidText("Dongeon", WIDTH, HEIGHT * 0.25 + 4);
	DrawMidText("Player Info", WIDTH, HEIGHT * 0.25 + 6);
	DrawMidText("Monster Info", WIDTH, HEIGHT * 0.25 + 8);
	DrawMidText("Weapon shop", WIDTH, HEIGHT * 0.25 + 10);
	DrawMidText("Save", WIDTH, HEIGHT * 0.25 + 12);
	DrawMidText("Exit", WIDTH, HEIGHT * 0.25 + 14);
}

void MapDraw::DongeonMenu()
{
	DrawMidText("===== 던전 입구 =====", WIDTH, HEIGHT * 0.2);
	DrawMidText("1층 던전 : [고블린]", WIDTH, HEIGHT * 0.2 + 6);
	DrawMidText("2층 던전 : [오크]", WIDTH, HEIGHT * 0.2 + 8);
	DrawMidText("3층 던전 : [늑대인간]", WIDTH, HEIGHT * 0.2 + 10);
	DrawMidText("4층 던전 : [오우거]", WIDTH, HEIGHT * 0.2 + 12);
	DrawMidText("5층 던전 : [스켈레톤아처]", WIDTH, HEIGHT * 0.2 + 14);
	DrawMidText("6층 던전 : [리치]", WIDTH, HEIGHT * 0.2 + 16);
	DrawMidText("돌아가기", WIDTH, HEIGHT * 0.2 + 18);
}

void MapDraw::RSPGmaeDraw()
{
	BoxDraw(0, 0, WIDTH, HEIGHT);
	RED
	DrawMidText("------------------------- vs -------------------------", WIDTH, HEIGHT * 0.5);
	YELLOW
	DrawMidText("가위 : 1   바위 : 2   보 : 3", WIDTH, HEIGHT * 0.1 + 6);
	ORIGINAL
}

void MapDraw::RSPResultDraw(string pRSP, string mRSP, string pResult, string mResult)
{
	YELLOW
	DrawMidText(pRSP, WIDTH, HEIGHT * 0.4);
	RED
	DrawMidText(pResult, WIDTH, HEIGHT * 0.4 + 1);
	DrawMidText(mResult, WIDTH, HEIGHT * 0.6);
	ORIGINAL
	DrawMidText(mRSP, WIDTH, HEIGHT * 0.6 + 1);
}

string MapDraw::KoreanRSP(int rsp)
{
	if (rsp == SCISSORS)
		return "가위";
	else if (rsp == ROCK)
		return "바위";
	else
		return "보";
}

void MapDraw::ShopMenu()
{
	DrawMidText("♧ ♣ S H O P ♣ ♧", WIDTH, HEIGHT * 0.25);
	DrawMidText("Dagger", WIDTH, HEIGHT * 0.25 + 2);
	DrawMidText("Gun", WIDTH, HEIGHT * 0.25 + 4);
	DrawMidText("Sword", WIDTH, HEIGHT * 0.25 + 6);
	DrawMidText("Wand", WIDTH, HEIGHT * 0.25 + 8);
	DrawMidText("Bow", WIDTH, HEIGHT * 0.25 + 10);
	DrawMidText("Hammer", WIDTH, HEIGHT * 0.25 + 12);
	DrawMidText("돌아가기", WIDTH, HEIGHT * 0.25 + 14);
}

void MapDraw::FileMenu()
{
	fstream load;
	string str, file;
	int height = 0;

	BoxDraw(0, 0, WIDTH, HEIGHT);
	GREEN
		for (int i = 1; i <= 10; i++)
		{
			file = "SavePlayer" + to_string(i) + ".txt";

			load.open(file);
			if (load.is_open())
				str = to_string(i) + "번슬롯 : (파일여부 : O)";
			else
				str = to_string(i) + "번슬롯 : (파일여부 : X)";
			load.close();
			DrawMidText(str, WIDTH, HEIGHT * 0.15 + height);
			height += 2;
		}
	DrawMidText("11.돌아가기", WIDTH, HEIGHT * 0.15 + height);
	ORIGINAL
}

MapDraw::~MapDraw()
{
}