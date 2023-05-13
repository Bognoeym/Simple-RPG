#include "GameManager.h"


GameManager::GameManager()
{
	m_iGameState = NORMAL;
	m_iLoadState = STARTTYPE_NEWSTART;
}

void GameManager::SetCharacter(string pFile, string mFile)
{
	Monster monster;
	int monsterCount = 0;
	player.LoadInfo(pFile, monsterCount, m_iLoadState);

	for (int i = 0; i < MAXMONSTER; i++)
	{
		monster.LoadInfo(mFile, monsterCount, m_iLoadState);
		monsterList.push_back(monster);
		monsterCount++;
	}
}

void GameManager::GameStart()
{
	int Select;
	while (1)
	{
		MapDrawManager.BoxDraw(0, 0, WIDTH, HEIGHT);
		MapDrawManager.FirstMenu();
		Select = MapDrawManager.MenuSelectCursor(3, HEIGHT * 0.1, WIDTH * 0.37, HEIGHT * 0.5);
		m_iGameState = NORMAL;
		m_iLoadState = STARTTYPE_NEWSTART;
		monsterList.clear();

		switch (Select)
		{
		case FIRSTMENU_NEWGAME:
			system("cls");
			SetCharacter("DefaultPlayer.txt", "DefaultMonster.txt");
			EnterNewGame();
			break;

		case FIRSTMENU_LOADGAME:
			system("cls");
			EnterLoadGame();
			if (m_iLoadState)
				EnterNewGame();
			break;

		case FIRSTMENU_GAMEEXIT:
			return;
		}
	}
}

void GameManager::EnterNewGame()
{
	int Select;
	if (!m_iLoadState)
		SetPlayerName();
	system("cls");
	while (1)
	{
		if (m_iGameState == PLAYERGAMEOVER)  // 플레이어 사망시
			return;
		MapDrawManager.BoxDraw(0, 0, WIDTH, HEIGHT);
		MapDrawManager.GameMenu();
		Select = MapDrawManager.MenuSelectCursor(6, 2, WIDTH * 0.34, HEIGHT * 0.25 + 4);
		m_iGameState = NORMAL;

		switch (Select)
		{
		case GAMEMENU_DONGEON:
			system("cls");
			EnterDongeon();
			break;

		case GAMEMENU_PLAYERINFO:
			system("cls");
			MapDrawManager.BoxDraw(0, 0, WIDTH, HEIGHT);
			YELLOW
			player.PrintInfo(HEIGHT * 0.5);
			player.WeaponInfo(HEIGHT * 0.5 + 4);
			ORIGINAL
				getch();
			break;

		case GAMEMENU_MONSTERINFO:
			system("cls");
			MapDrawManager.BoxDraw(0, 0, WIDTH, HEIGHT);
			PrintMonsterInfo();
			getch();
			break;

		case GAMEMENU_WEAPONSHOP:
			system("cls");
			fileManager.SetWeapon(&weaponList);
			shopManager.EnterShop(&weaponList, &player);
			break;

		case GAMEMENU_SAVE:
			system("cls");
			fileManager.SaveFile(&monsterList, &player);
			break;

		case GAMEMENU_EXIT:
			monsterList.clear();
			return;
		}
	}
}

void GameManager::EnterDongeon()
{
	int Select;
	while (1)
	{
		if (m_iGameState > NORMAL)  // 플레이어나 몬스터 사망시
			return;

		MapDrawManager.BoxDraw(0, 0, WIDTH, HEIGHT);
		MapDrawManager.DongeonMenu();
		Select = MapDrawManager.MenuSelectCursor(7, 2, WIDTH * 0.25, HEIGHT * 0.2 + 6);

		switch (Select)
		{
		case MONSTER_GOBLIN:
			RSPGameStart(MONSTER_GOBLIN);
			return;

		case MONSTER_OAK:
			RSPGameStart(MONSTER_OAK);
			return;

		case MONSTER_WOLFMAN:
			RSPGameStart(MONSTER_WOLFMAN);
			return;

		case MONSTER_OAGER:
			RSPGameStart(MONSTER_OAGER);
			return;

		case MONSTER_SKELETON:
			RSPGameStart(MONSTER_SKELETON);
			return;

		case MONSTER_RICH:
			RSPGameStart(MONSTER_RICH);
			return;

		case MONSTER_RETURN:
			return;
		}
	}
}

void GameManager::RSPGameStart(int monsterNum)
{
	system("cls");
	int monster = monsterNum - 1;

	MapDrawManager.RSPGmaeDraw();
	while (1)
	{
		if (m_iGameState > NORMAL)  // 플레이어나 몬스터 사망시
			return;
		YELLOW
		player.PrintInfo(HEIGHT * 0.1);
		if (player.GetHasWeapon())
			player.WeaponInfo(HEIGHT * 0.1 + 4);
		ORIGINAL
		monsterList.at(monster).PrintInfo(HEIGHT * 0.8);
		monsterList.at(monster).RockScisPaper();
		player.RockScisPaper();
		RSPCheck(player.GetInfo(INFOTYPE_RSP), monsterList.at(monster).GetInfo(INFOTYPE_RSP), monster);
	}
}

void GameManager::WinCheck(int win, int monsterNum)
{
	Monster tmp = monsterList.at(monsterNum);
	string name;
	int exp;

	if (win == PLAYERWIN)  // 플레이어 승
	{
		name = player.GetName();
		exp = tmp.GetInfo(INFOTYPE_GETEXP);
		player.ControlInfo(INFOTYPE_NOWEXP, tmp.GetInfo(INFOTYPE_GETEXP));
		player.ControlInfo(INFOTYPE_GOLD, tmp.GetInfo(INFOTYPE_GOLD));
	}
	else
	{
		name = tmp.GetName();
		exp = player.GetInfo(INFOTYPE_GETEXP);
		tmp.ControlInfo(INFOTYPE_NOWEXP, player.GetInfo(INFOTYPE_GETEXP));
	}

	system("cls");
	MapDrawManager.BoxDraw(0, 0, WIDTH, HEIGHT);
	RED
	MapDrawManager.DrawMidText(name + " 승리!!", WIDTH, HEIGHT * 0.4);
	MapDrawManager.DrawMidText(name + " 가 경험치 " + to_string(exp) + "를 얻었습니다.",
		WIDTH, HEIGHT * 0.5);
	ORIGINAL;
	getch();
}

void GameManager::RSPCheck(int playerRSP, int monsterRSP, int monsterNum)
{
	MapDrawManager.DrawMidText("                        ", WIDTH, HEIGHT * 0.5 - 1);
	string pResult, mResult;
	string pRSP = MapDrawManager.KoreanRSP(playerRSP);
	string mRSP = MapDrawManager.KoreanRSP(monsterRSP);
	int specialRand = rand() % 3;  // 필살기 발동 확률 = 1/3

	if (playerRSP == monsterRSP)
	{
		pResult = "Draw";
		mResult = "Draw";
		MapDrawManager.RSPResultDraw(pRSP, mRSP, pResult, mResult);
	}
	else if ((playerRSP == SCISSORS && monsterRSP == PAPER) || (playerRSP == ROCK && monsterRSP == SCISSORS)  // 플레이어 승
		|| (playerRSP == PAPER && monsterRSP == ROCK))
	{
		pResult = " Win ";
		mResult = "Lose";
		MapDrawManager.RSPResultDraw(pRSP, mRSP, pResult, mResult);

		if (specialRand == 1 && player.GetHasWeapon())  // 필살기
		{
			Weapon* tmp = player.GetWeapon();
			int special = tmp->SpecialAttack();

			if (special == 5)
			{
				player.ControlInfo(INFOTYPE_NOWHEALTH, 5);
				if (player.GetInfo(INFOTYPE_NOWHEALTH) > player.GetInfo(INFOTYPE_MAXHEALTH))
					player.ResetHealth();
			}
			else
			{
				if (special != 0)
					special += player.GetInfo(INFOTYPE_ATTACK);
				monsterList.at(monsterNum).ControlInfo(INFOTYPE_NOWHEALTH, -special);
			}
		}
		else if (player.GetHasWeapon())  // 무기O
		{
			Weapon* tmp = player.GetWeapon();
			monsterList.at(monsterNum).ControlInfo(INFOTYPE_NOWHEALTH, -(player.GetInfo(INFOTYPE_ATTACK)+tmp->GetAttack()));
		}
		else  // 기본, 무기X 
			monsterList.at(monsterNum).ControlInfo(INFOTYPE_NOWHEALTH, -player.GetInfo(INFOTYPE_ATTACK));

		if (monsterList.at(monsterNum).GetInfo(INFOTYPE_NOWHEALTH) <= 0)  // 몬스터 죽음
		{
			monsterList.at(monsterNum).ControlInfo(INFOTYPE_NOWHEALTH, -monsterList.at(monsterNum).GetInfo(INFOTYPE_NOWHEALTH));
			monsterList.at(monsterNum).PrintInfo(HEIGHT * 0.8);
			getch();
			WinCheck(PLAYERWIN, monsterNum);
			player.LevelUpCheck();
			monsterList.at(monsterNum).ResetHealth();
			m_iGameState = MONGAMEOVER;
			return;
		}
	}
	else  // 몬스터 승
	{
		pResult = "Lose";
		mResult = " Win ";
		MapDrawManager.RSPResultDraw(pRSP, mRSP, pResult, mResult);
		player.ControlInfo(INFOTYPE_NOWHEALTH, -monsterList.at(monsterNum).GetInfo(INFOTYPE_ATTACK));

		if (player.GetInfo(INFOTYPE_NOWHEALTH) <= 0)  // 플레이어 죽음
		{
			WinCheck(MONSTERWIN, monsterNum);
			m_iGameState = PLAYERGAMEOVER;
			RED
			MapDrawManager.DrawMidText("Game Over", WIDTH, HEIGHT * 0.6);
			ORIGINAL
			getch();
			return;
		}
	}
}

void GameManager::EnterLoadGame()
{
	ifstream load;
	string str, file;
	int height = 0;
	int select;

	while (!m_iLoadState)
	{
		system("cls");
		MapDrawManager.FileMenu();
		select = MapDrawManager.MenuSelectCursor(11, 2, WIDTH * 0.2, HEIGHT * 0.15);

		if (select == 11)
			return;
		else
		{
			//if (fileManager.LoadFile(select))
			//{
			//	m_iLoadState = STARTTYPE_LOADSTART;
			//}
			LoadFile(select);
			height = 0;
		}
	}
}

void GameManager::LoadFile(int select)
{
	ifstream load;
	string str = "SavePlayer" + to_string(select) + ".txt";

	load.open(str);
	if (load.is_open())
	{
		m_iLoadState = STARTTYPE_LOADSTART;
		SetCharacter(str, "SaveMonster" + to_string(select) + ".txt");
		fileManager.LoadWeapon(str, &player);
		system("cls");
		MapDrawManager.BoxDraw(0, 0, WIDTH, HEIGHT);
		MapDrawManager.DrawMidText("Load 완료", WIDTH, HEIGHT * 0.5);
	}
	else
	{
		system("cls");
		MapDrawManager.BoxDraw(0, 0, WIDTH, HEIGHT);
		MapDrawManager.DrawMidText("해당 파일이 없습니다.", WIDTH, HEIGHT * 0.5);
	}
	getch();
}

void GameManager::SetPlayerName()
{
	string name;
	MapDrawManager.BoxDraw(0, 0, WIDTH, HEIGHT);
	YELLOW
	MapDrawManager.DrawMidText("Player 이름 입력 : ", WIDTH, HEIGHT * 0.5);
	cin >> name;
	player.SetName(name);
	ORIGINAL
}

void GameManager::PrintMonsterInfo()
{
	int height = HEIGHT * 0.1;
	for (auto iter = monsterList.begin(); iter != monsterList.end(); iter++)
	{
		iter->PrintInfo(height);
		height += 4;
	}
}

GameManager::~GameManager()
{
	for (int i = 0; i < weaponList.size(); i++)
		delete weaponList.at(i);
}