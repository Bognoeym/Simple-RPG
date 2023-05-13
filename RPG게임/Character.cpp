#include "Character.h"

Character::Character()
{

}

void Character::SetCharacter(string info, int* startType)
{
	stringstream ss(info);

	ss >> m_sName >> m_iAttackPoint >> m_iMaxHealth >> m_iMaxEXP >> m_iGetEXP >>
		m_iLevel >> m_iGold;


	if (*startType == STARTTYPE_LOADSTART)
	{
		ss >> m_iNowEXP >> m_iNowHealth;
	}
	else
	{
		ResetHealth();
		ResetEXP();
	}
}

void Character::ControlInfo(int type, int value)
{
	switch (type)
	{
	case INFOTYPE_ATTACK:
		m_iAttackPoint += value;
		break;

	case INFOTYPE_NOWHEALTH:
		m_iNowHealth += value;
		break;

	case INFOTYPE_NOWEXP:
		m_iNowEXP += value;
		m_iGetEXP += value;
		break;

	case INFOTYPE_GOLD:
		m_iGold += value;
		break;

	case INFOTYPE_LEVEL:
		m_iLevel += value;
		break;
	}
}

int Character::GetInfo(int type)
{
	switch (type)
	{
	case INFOTYPE_ATTACK:
		return m_iAttackPoint;

	case INFOTYPE_MAXHEALTH:
		return m_iMaxHealth;

	case INFOTYPE_MAXEXP:
		return m_iMaxEXP;

	case INFOTYPE_NOWHEALTH:
		return m_iNowHealth;

	case INFOTYPE_NOWEXP:
		return m_iNowEXP;

	case INFOTYPE_GETEXP:
		return m_iGetEXP;

	case INFOTYPE_GOLD:
		return m_iGold;

	case INFOTYPE_LEVEL:
		return m_iLevel;

	case INFOTYPE_RSP:
		return m_iRSP;
	}
}

void Character::LevelUpCheck()
{
	if (m_iNowEXP >= m_iMaxEXP)
	{
		m_iLevel++;
		m_iNowEXP = 0;
		m_iGetEXP = 0;
		m_iMaxEXP += 3;
		m_iAttackPoint += 4;
		m_iMaxHealth += 8;
		m_iNowHealth = m_iMaxHealth;

		MapDrawManager.BoxDraw(0, 0, WIDTH, HEIGHT);
		PUPPLE
		MapDrawManager.DrawMidText(m_sName + "레벨업!!", WIDTH, HEIGHT * 0.4);
		MapDrawManager.DrawMidText("공격력 4 증가!!", WIDTH, HEIGHT * 0.5);
		MapDrawManager.DrawMidText("생명력 8 증가!!", WIDTH, HEIGHT * 0.6);
		ORIGINAL
			getch();
	}
	else
		return;
}

void Character::PrintInfo(int height)
{
	MapDrawManager.DrawMidText("======" + m_sName + "(" + to_string(m_iLevel) + "Lv)======", WIDTH, height++);
	MapDrawManager.DrawMidText("공격력 = " + to_string(m_iAttackPoint), WIDTH - 10, height);
	MapDrawManager.DrawMidText("생명력 = " + to_string(m_iNowHealth) + "/" + to_string(m_iMaxHealth), WIDTH + 10, height++);
	MapDrawManager.DrawMidText("경험치 = " + to_string(m_iNowEXP) + "/" + to_string(m_iMaxEXP), WIDTH - 9, height);
	MapDrawManager.DrawMidText("GetEXP : " + to_string(m_iGetEXP), WIDTH + 8, height++);
	MapDrawManager.DrawMidText("Gold = " + to_string(m_iGold), WIDTH - 10, height);
}