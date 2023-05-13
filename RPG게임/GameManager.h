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
#include "FileManager.h"
#include "ShopManager.h"

class GameManager
{
private:
	int m_iGameState;
	int m_iLoadState;
	vector<Weapon*> weaponList;
	vector<Monster> monsterList;
	Player player;
	MapDraw MapDrawManager;
	ShopManager shopManager;
	FileManager fileManager;


public:
	GameManager();
	void GameStart();
	void EnterNewGame();
	void EnterLoadGame();
	void EnterDongeon();
	//void EnterShop(); 
	void SetPlayerName();
	void SetCharacter(string pFile, string mFile);
	//void SetWeapon();
	void PrintMonsterInfo();
	//void PrintWeaponList(string type);
	//void PrintWeaponInfo(vector<Weapon*> tmpList, int start, int end, int &height);
	void RSPGameStart(int monster);
	void RSPCheck(int playerRSP, int monsterRSP, int monsterNum);
	void WinCheck(int win, int monsterNum);
	//void BuyWeapon(vector<Weapon*> tmpList, int select, int page);
	void LoadFile(int select);
	//void LoadWeapon(string pFile);
	//void SaveFile();
	~GameManager();
};

