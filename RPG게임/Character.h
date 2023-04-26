#pragma once
#include "Mecro.h"
#include "MapDraw.h"

class Character
{
protected:
	int m_iAttackPoint;
	int m_iMaxHealth;
	int m_iNowHealth;
	int m_iMaxEXP;
	int m_iNowEXP;
	int m_iGetEXP;
	int m_iGold;
	int m_iLevel;
	int m_iRSP;
	string m_sName;
	MapDraw MapDrawManager;
public:
	Character();
	inline void ResetHealth() { m_iNowHealth = m_iMaxHealth; }
	inline void ResetEXP() { m_iNowEXP = 0; }
	inline string GetName() { return m_sName; }
	int GetInfo(int type);
	void LoadInfo(string fileName, int monsterCount, int startType);
	void PrintInfo(int height);
	void ControlInfo(int type, int value);
	void LevelUpCheck();
	virtual void RockScisPaper() = 0;
};