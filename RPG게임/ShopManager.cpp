#include "ShopManager.h"

ShopManager::ShopManager()
{

}

void ShopManager::EnterShop(vector<Weapon*>* weaponList, Player* player)
{
	int Select;

	while (1)
	{
		MapDrawManager.BoxDraw(0, 0, WIDTH, HEIGHT);
		MapDrawManager.ShopMenu();
		Select = MapDrawManager.MenuSelectCursor(7, 2, WIDTH * 0.25, HEIGHT * 0.25 + 2);

		switch (Select)
		{
		case WEAPON_DAGGER:
			system("cls");
			PrintWeaponList("대거", weaponList, player);
			break;

		case WEAPON_GUN:
			system("cls");
			PrintWeaponList("총", weaponList, player);
			break;

		case WEAPON_SWORD:
			system("cls");
			PrintWeaponList("장검", weaponList, player);
			break;

		case WEAPON_WAND:
			system("cls");
			PrintWeaponList("지팡이", weaponList, player);
			break;

		case WEAPON_BOW:
			system("cls");
			PrintWeaponList("활", weaponList, player);
			break;

		case WEAPON_HAMMER:
			system("cls");
			PrintWeaponList("해머", weaponList, player);
			break;

		case 7:
			system("cls");
			return;
		}
	}
}

void ShopManager::PrintWeaponList(string type, vector<Weapon*>* weaponList, Player* player)
{
	vector<Weapon*> tmpList;
	int height;
	int page = 1;
	int select, size;

	for (int i = 0; i < weaponList->size(); i++)
	{
		if (weaponList->at(i)->GetType() == type)
			tmpList.push_back(weaponList->at(i));
	}

	while (1)
	{
		system("cls");
		MapDrawManager.BoxDraw(0, 0, WIDTH, HEIGHT);
		MapDrawManager.DrawMidText("보유 Gold : " + to_string(player->GetInfo(INFOTYPE_GOLD)), WIDTH, HEIGHT * 0.07);
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
			BuyWeapon(tmpList, select, page, player);
	}
	getch();
}

void ShopManager::BuyWeapon(vector<Weapon*> tmpList, int select, int page, Player* player)
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

	if (player->GetInfo(INFOTYPE_GOLD) < tmp->GetPrice())
		return;

	player->ControlInfo(INFOTYPE_GOLD, -tmp->GetPrice());
	player->SetWeapon(tmp);
}

void ShopManager::PrintWeaponInfo(vector<Weapon*> tmpList, int start, int end, int& height)
{
	for (int i = start; i < end; i++)
	{
		tmpList.at(i)->PrintInfo(HEIGHT * 0.07 + height);
		height += 3;
	}
}

ShopManager::~ShopManager()
{

}