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
	vector<Monster> monsterList, *originalMList;
	Player player, *originalPlayer;
	MapDraw MapDrawManager;
	ShopManager shopManager;
	FileManager fileManager;


public:
	GameManager();
	void Init();
	void InitCharacter();
	void GameStart();
	void EnterGame();
	void EnterLoadGame();
	void EnterDongeon();
	void SetPlayerName();
	void PrintMonsterInfo();
	void RSPGameStart(int monster);
	void RSPCheck(int playerRSP, int monsterRSP, int monsterNum);
	void WinCheck(int win, int monsterNum);
	//void LoadFile(int select);
	~GameManager();
};

