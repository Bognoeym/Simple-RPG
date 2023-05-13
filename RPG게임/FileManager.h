#pragma once
#include "MapDraw.h"
#include "Player.h"
#include "Monster.h"
#include "Weapon.h"
#include "Bow.h"
#include "Dagger.h"
#include "Gun.h"
#include "Sword.h"
#include "Wand.h"
#include "Hammer.h"

class FileManager
{
private:
	MapDraw MapDrawManager;

public:
	FileManager();
	void SetWeapon(vector<Weapon*>* weaponList);
	void SaveFile(vector<Monster>* monsterList, Player* player);
	bool LoadFile(int select);
	void LoadWeapon(string pFile, Player* player);
	~FileManager();
};

