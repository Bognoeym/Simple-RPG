#include "Weapon.h"

Weapon::Weapon()
{

}

void Weapon::PrintInfo(int height)
{
	MapDrawManager.DrawMidText("가격 : " + to_string(m_iPrice) + " 무기타입 : " + m_sWPType, WIDTH, height++);
	MapDrawManager.DrawMidText("무기이름 : " +m_sWPName+" 공격력 : "+to_string(m_iAttackPoint), WIDTH, height);
}

Weapon::~Weapon()
{

}