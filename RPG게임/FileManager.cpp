#include "FileManager.h"

FileManager::FileManager()
{

}

void FileManager::SaveFile(vector<Monster>* monsterList, Player* player)
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
			save << player->GetName() << " ";
			for (int i = INFOTYPE_ATTACK; i <= INFOTYPE_NOWHEALTH; i++)
			{
				save << player->GetInfo(i) << " ";
			}

			save << "\n" << player->GetHasWeapon() << " ";
			if (player->GetHasWeapon())
			{
				Weapon* tmp = player->GetWeapon();
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
				save << monsterList->at(i).GetName() << " ";
				for (int j = INFOTYPE_ATTACK; j <= INFOTYPE_NOWHEALTH; j++)
				{
					save << monsterList->at(i).GetInfo(j) << " ";
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

bool FileManager::LoadFile(string pFile, string mFile, Player* player, 
	vector<Monster>* monsterList, int* loadState)
{
	if (PlayerFile(pFile, player, loadState))
	{
		MonsterFile(mFile, monsterList, loadState);
		system("cls");
		MapDrawManager.BoxDraw(0, 0, WIDTH, HEIGHT);
		MapDrawManager.DrawMidText("Load 완료", WIDTH, HEIGHT * 0.5);
		getch();
		return true;
	}
	else
	{
		system("cls");
		MapDrawManager.BoxDraw(0, 0, WIDTH, HEIGHT);
		MapDrawManager.DrawMidText("해당 파일이 없습니다.", WIDTH, HEIGHT * 0.5);
	}

	getch();
	return false;
}

void FileManager::MonsterFile(string fileName, vector<Monster>* monsterList, int* loadState)
{
	ifstream load;
	string tmp;

	load.open(fileName);
	if (load.is_open())
	{
		Monster monster;

		for (int i = 0; i < MAXMONSTER; i++)
		{
			getline(load, tmp);
			monster.SetCharacter(tmp, loadState);
			monsterList->push_back(monster);
		}

		load.close();
	}
}

bool FileManager::PlayerFile(string fileName, Player* player, int* loadState)
{
	ifstream load;
	string tmp;

	load.open(fileName);  // player 파일 읽기

	if (load.is_open())
	{
		getline(load, tmp);
		player->SetCharacter(tmp, loadState);
		getline(load, tmp);
		LoadWeapon(tmp, player);
		load.close();
		return true;
	}

	return false;
}

void FileManager::LoadWeapon(string info, Player* player)
{
	int weapon;
	stringstream ss(info);
	string str;
	ss >> weapon;
	
	if (weapon == false)
		return;
	else
	{
		Weapon* tmp;
		ss >> str;
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
		ss >> str;
		tmp->SetName(str);
		ss >> weapon;
		tmp->SetAttack(weapon);
		ss >> weapon;
		tmp->SetPrice(weapon);
		player->SetWeapon(tmp);
	}
}

void FileManager::SetWeapon(vector<Weapon*>* weaponList)
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
			weaponList->push_back(tmp);
		}
	}
	else
		cout << "파일 없음" << endl;
}

FileManager::~FileManager()
{

}