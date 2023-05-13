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
//#include "Mecro.h"

class FileManager
{
private:
	MapDraw MapDrawManager;

public:
	FileManager();
	void SetWeapon(vector<Weapon*>* weaponList);
	void SaveFile(vector<Monster>* monsterList, Player* player);
	bool LoadFile(string pFile, string mFile, Player* player, vector<Monster>* monsterList, int* loadState);
	bool PlayerFile(string fileName, Player* player, int* loadState);
	void MonsterFile(string fileName, vector<Monster>* monsterList, int* loadState);
	void LoadWeapon(string pFile, Player* player);
	~FileManager();
};

