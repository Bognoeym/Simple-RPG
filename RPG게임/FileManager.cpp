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
		file += to_string(select) + ".txt";  // �÷��̾� ����
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

		file = "SaveMonster" + to_string(select) + ".txt";  // ���� ����
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
		MapDrawManager.DrawMidText("Save �Ϸ�", WIDTH, HEIGHT * 0.5);
		getch();
	}
}

void FileManager::LoadWeapon(string pFile, Player* player)
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
			if (str == "Ȱ")
				tmp = new Bow;
			else if (str == "���")
				tmp = new Dagger;
			else if (str == "��")
				tmp = new Gun;
			else if (str == "���")
				tmp = new Sword;
			else if (str == "������")
				tmp = new Wand;
			else if (str == "�ظ�")
				tmp = new Hammer;
			tmp->SetType(str);
			load >> str;
			tmp->SetName(str);
			load >> weapon;
			tmp->SetAttack(weapon);
			load >> weapon;
			tmp->SetPrice(weapon);
			player->SetWeapon(tmp);
		}
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
				tmp->SetType("Ȱ");
			}
			else if (str == "Dagger")
			{
				tmp = new Dagger;
				tmp->SetType("���");
			}
			else if (str == "Gun")
			{
				tmp = new Gun;
				tmp->SetType("��");
			}
			else if (str == "Sword")
			{
				tmp = new Sword;
				tmp->SetType("���");
			}
			else if (str == "Wand")
			{
				tmp = new Wand;
				tmp->SetType("������");
			}
			else if (str == "Hammer")
			{
				tmp = new Hammer;
				tmp->SetType("�ظ�");
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
		cout << "���� ����" << endl;
}

FileManager::~FileManager()
{

}