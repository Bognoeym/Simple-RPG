#pragma once
#include "MapDraw.h"
#include "Weapon.h"
#include "Bow.h"
#include "Dagger.h"
#include "Gun.h"
#include "Sword.h"
#include "Wand.h"
#include "Hammer.h"
#include "FileManager.h"

class ShopManager
{
private:
	MapDraw MapDrawManager;
	FileManager m_FileManager;

public:
	ShopManager();
	void EnterShop(vector<Weapon*>* weaponList, Player* player);
	void PrintWeaponList(string type, vector<Weapon*>* weaponList, Player* player);
	void PrintWeaponInfo(vector<Weapon*> tmpList, int start, int end, int& height);
	void BuyWeapon(vector<Weapon*> tmpList, int select, int page, Player* player);
	~ShopManager();
};

