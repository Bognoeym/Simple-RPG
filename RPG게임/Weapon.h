#pragma once
#include "Mecro.h"
#include "MapDraw.h"

class Weapon
{
protected:
	int m_iPrice;
	int m_iAttackPoint;
	string m_sWPType;
	string m_sWPName;
	MapDraw MapDrawManager;

public:
	Weapon();
	inline void SetPrice(int price) { m_iPrice = price; }
	inline void SetAttack(int attack) { m_iAttackPoint = attack; }
	inline void SetType(string type) { m_sWPType = type; }
	inline void SetName(string name) { m_sWPName = name; }
	inline string GetType() { return m_sWPType; }
	inline string GetName() { return m_sWPName; }
	inline int GetAttack() { return m_iAttackPoint; }
	inline int GetPrice() { return m_iPrice; }
	void PrintInfo(int height);
	virtual int SpecialAttack() = 0;
	virtual ~Weapon();
};

