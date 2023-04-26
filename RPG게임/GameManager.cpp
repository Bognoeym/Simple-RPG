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
			EnterShop();
			break;

		case GAMEMENU_SAVE:
			system("cls");
			SaveFile();
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

void GameManager::EnterShop()
{
	int Select;
	SetWeapon();
	while (1)
	{
		MapDrawManager.BoxDraw(0, 0, WIDTH, HEIGHT);
		MapDrawManager.ShopMenu();
		Select = MapDrawManager.MenuSelectCursor(7, 2, WIDTH * 0.25, HEIGHT * 0.25 + 2);

		switch (Select)
		{
		case WEAPON_DAGGER:
			system("cls");
			PrintWeaponList("대거");
			break;

		case WEAPON_GUN:
			system("cls");
			PrintWeaponList("총");
			break;

		case WEAPON_SWORD:
			system("cls");
			PrintWeaponList("장검");
			break;

		case WEAPON_WAND:
			system("cls");
			PrintWeaponList("지팡이");
			break;

		case WEAPON_BOW:
			system("cls");
			PrintWeaponList("활");
			break;

		case WEAPON_HAMMER:
			system("cls");
			PrintWeaponList("해머");
			break;

		case 7:
			system("cls");
			return;
		}
	}
}

void GameManager::PrintWeaponList(string type)
{
	vector<Weapon*> tmpList;
	int height;
	int page = 1;
	int select, size;

	for (int i = 0; i < weaponList.size(); i++)
	{
		if (weaponList.at(i)->GetType() == type)
			tmpList.push_back(weaponList.at(i));
	}

	while (1)
	{
		system("cls");
		MapDrawManager.BoxDraw(0, 0, WIDTH, HEIGHT);
		MapDrawManager.DrawMidText("보유 Gold : " + to_string(player.GetInfo(INFOTYPE_GOLD)), WIDTH, HEIGHT * 0.07);
		MapDrawManager.DrawMidText(type + " Shop", WIDTH, HEIGHT * 0.07 + 2);
		height = 4;

		if (tmpList.size() > MAXPAGEOFWP && page == PAGE1) 
		{
			YELLOW;
			PrintWeaponInfo(tmpList, 0, MAXPAGEOFWP, height);
			ORIGINAL;
		}
		else if (tmpList.size() > MAXPAGEOFWP && page == PAGE2)
		{
			YELLOW;
			PrintWeaponInfo(tmpList, MAXPAGEOFWP, tmpList.size(), height);
			ORIGINAL;
		}
		else
		{
			YELLOW;
			PrintWeaponInfo(tmpList, 0, tmpList.size(), height);
			ORIGINAL;
		}

		if (tmpList.size() < MAXPAGEOFWP)
			size = tmpList.size();
		else if (tmpList.size() > MAXPAGEOFWP && page == PAGE2)
			size = tmpList.size() - MAXPAGEOFWP;
		else
			size = MAXPAGEOFWP;

		MapDrawManager.DrawMidText("이전페이지", WIDTH, HEIGHT * 0.07 + height);
		MapDrawManager.DrawMidText("다음페이지", WIDTH, HEIGHT * 0.07 + height + 3);
		MapDrawManager.DrawMidText("나가기", WIDTH, HEIGHT * 0.07 + height + 6);

		select = MapDrawManager.MenuSelectCursor(size + 3, 3, WIDTH * 0.2, HEIGHT * 0.07 + 4);

		if (select == size + 3)
			return;
		if ((select == size + 1 && page == PAGE1) || (select == size + 2 && page == PAGE2))
			continue;
		else if (select == size + 2)  // 다음 페이지
			page++;
		else if (select == size + 1)  // 이전 페이지
			page--;
		else
			BuyWeapon(tmpList, select, page);
	}
	getch();
}

void GameManager::BuyWeapon(vector<Weapon*> tmpList, int select, int page)
{
	Weapon* tmp;

	if (page == PAGE1)
	{
		tmp = tmpList.at(select - 1);
	}
	else if (page == PAGE2)
	{
		tmp = tmpList.at(MAXPAGEOFWP + select - 1);
	}

	if (player.GetInfo(INFOTYPE_GOLD) < tmp->GetPrice())
		return;

	player.ControlInfo(INFOTYPE_GOLD, -tmp->GetPrice());
	player.SetWeapon(tmp);
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
		LoadWeapon(str);
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

void GameManager::LoadWeapon(string pFile)
{
	ifstream load;
	string str, str2;
	int weapon;

	load.open(pFile);
	if (load.is_open())
	{
		getline(load, str2);
		load >> weapon;

		if (weapon == false)
			return;
		else
		{
			Weapon* tmp;
			load >> str;
			if (str == "활")
				tmp = new Bow;
			else if (str == "대거")
				tmp = new Dagger;
			else if (str == "총")
				tmp = new Gun;
			else if (str == "장검")
				tmp = new Sword;
			else if (str == "지팡이")
				tmp = new Wand;
			else if (str == "해머")
				tmp = new Hammer;
			tmp->SetType(str);
			load >> str;
			tmp->SetName(str);
			load >> weapon;
			tmp->SetAttack(weapon);
			load >> weapon;
			tmp->SetPrice(weapon);
			player.SetWeapon(tmp);
		}
	}
}

void GameManager::SaveFile()
{
	ofstream save;
	string file = "SavePlayer";
	int select;

	MapDrawManager.FileMenu();
	select = MapDrawManager.MenuSelectCursor(11, 2, WIDTH * 0.2, HEIGHT * 0.15);

	if (select == 11)
		return;
	else
	{
		file += to_string(select) + ".txt";  // 플레이어 저장
		save.open(file);
		if (save.is_open())
		{
			save << player.GetName() << " ";
			for (int i = INFOTYPE_ATTACK; i <= INFOTYPE_NOWHEALTH; i++)
			{
				save << player.GetInfo(i) << " ";
			}

			save << "\n" << player.GetHasWeapon() << " ";
			if (player.GetHasWeapon())
			{
				Weapon* tmp = player.GetWeapon();
				save << tmp->GetType() << " " << tmp->GetName() << " " << tmp->GetAttack() << " " << tmp->GetPrice();
			}
			save.close();
		}

		file = "SaveMonster" + to_string(select) + ".txt";  // 몬스터 저장
		save.open(file);
		if (save.is_open())
		{
			for (int i = 0; i < MAXMONSTER; i++)
			{
				save << monsterList.at(i).GetName() << " ";
				for (int j = INFOTYPE_ATTACK; j <= INFOTYPE_NOWHEALTH; j++)
				{
					save << monsterList.at(i).GetInfo(j) << " ";
				}
				save << "\n";
			}
			save.close();
		}
		system("cls");
		MapDrawManager.BoxDraw(0, 0, WIDTH, HEIGHT);
		MapDrawManager.DrawMidText("Save 완료", WIDTH, HEIGHT * 0.5);
		getch();
	}
}

void GameManager::SetWeapon()
{
	ifstream load;
	Weapon* tmp;
	string str;
	int i;

	load.open("WeaponList.txt");

	if (load.is_open())
	{
		while (!load.eof())
		{
			load >> str;

			if (str == "Bow")
			{
				tmp = new Bow;
				tmp->SetType("활");
			}
			else if (str == "Dagger")
			{
				tmp = new Dagger;
				tmp->SetType("대거");
			}
			else if (str == "Gun")
			{
				tmp = new Gun;
				tmp->SetType("총");
			}
			else if (str == "Sword")
			{
				tmp = new Sword;
				tmp->SetType("장검");
			}
			else if (str == "Wand")
			{
				tmp = new Wand;
				tmp->SetType("지팡이");
			}
			else if (str == "Hammer")
			{
				tmp = new Hammer;
				tmp->SetType("해머");
			}
			load >> str;
			tmp->SetName(str);
			load >> i;
			tmp->SetAttack(i);
			load >> i;
			tmp->SetPrice(i);
			weaponList.push_back(tmp);
		}
	}
	else
		cout << "파일 없음" << endl;
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

void GameManager::PrintWeaponInfo(vector<Weapon*> tmpList, int start, int end, int &height)
{
	for (int i = start; i < end; i++)
	{
		tmpList.at(i)->PrintInfo(HEIGHT * 0.07 + height);
		height += 3;
	}
}

GameManager::~GameManager()
{
	for (int i = 0; i < weaponList.size(); i++)
		delete weaponList.at(i);
}