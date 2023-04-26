#pragma once
#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<string>
#include<fstream>
#include<time.h>
#include<vector>
using namespace std;

//////////////////////////////////////////////////////
#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define BLACK SetConsoleTextAttribute( col,0x0000 );
#define DARK_BLUE SetConsoleTextAttribute( col,0x0001 );
#define GREEN SetConsoleTextAttribute( col,0x0002 );
#define BLUE_GREEN SetConsoleTextAttribute( col,0x0003 );
#define BLOOD SetConsoleTextAttribute( col,0x0004 );
#define PUPPLE SetConsoleTextAttribute( col,0x0005 );
#define GOLD SetConsoleTextAttribute( col,0x0006 );			//색상 지정
#define ORIGINAL SetConsoleTextAttribute( col,0x0007 );
#define GRAY SetConsoleTextAttribute( col,0x0008 );
#define BLUE SetConsoleTextAttribute( col,0x0009 );
#define HIGH_GREEN SetConsoleTextAttribute( col,0x000a );
#define SKY_BLUE SetConsoleTextAttribute( col,0x000b );
#define RED SetConsoleTextAttribute( col,0x000c );
#define PLUM SetConsoleTextAttribute( col,0x000d );
#define YELLOW SetConsoleTextAttribute( col,0x000e );
//////////////////////////////////////////////////////
#define WIDTH 30
#define HEIGHT 30
#define MAXMONSTER 6
#define MAXPAGEOFWP 5

#define SCISSORS 1
#define ROCK 2
#define PAPER 3

#define MONSTERWIN 0
#define PLAYERWIN 1

#define NORMAL 0
#define MONGAMEOVER 1
#define PLAYERGAMEOVER 2

#define PAGE1 1
#define PAGE2 2


enum STARTTYPE
{
	STARTTYPE_NEWSTART,
	STARTTYPE_LOADSTART
};

enum FIRSTMENU
{
	FIRSTMENU_NEWGAME = 1,
	FIRSTMENU_LOADGAME,
	FIRSTMENU_GAMEEXIT
};

enum GAMEMENU
{
	GAMEMENU_DONGEON = 1,
	GAMEMENU_PLAYERINFO,
	GAMEMENU_MONSTERINFO,
	GAMEMENU_WEAPONSHOP,
	GAMEMENU_SAVE,
	GAMEMENU_EXIT
};

enum MONSTER
{
	MONSTER_GOBLIN = 1,
	MONSTER_OAK,
	MONSTER_WOLFMAN,
	MONSTER_OAGER,
	MONSTER_SKELETON,
	MONSTER_RICH,
	MONSTER_RETURN
};

enum INFOTYPE
{
	INFOTYPE_ATTACK,
	INFOTYPE_MAXHEALTH,
	INFOTYPE_MAXEXP,
	INFOTYPE_GETEXP,
	INFOTYPE_LEVEL,
	INFOTYPE_GOLD,
	INFOTYPE_NOWEXP,
	INFOTYPE_NOWHEALTH,
	INFOTYPE_RSP
};

enum WEAPON
{
	WEAPON_DAGGER = 1,
	WEAPON_GUN,
	WEAPON_SWORD,
	WEAPON_WAND,
	WEAPON_BOW,
	WEAPON_HAMMER
};