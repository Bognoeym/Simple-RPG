#include "Weapon.h"

Weapon::Weapon()
{

}

void Weapon::PrintInfo(int height)
{
	MapDrawManager.DrawMidText("���� : " + to_string(m_iPrice) + " ����Ÿ�� : " + m_sWPType, WIDTH, height++);
	MapDrawManager.DrawMidText("�����̸� : " +m_sWPName+" ���ݷ� : "+to_string(m_iAttackPoint), WIDTH, height);
}

Weapon::~Weapon()
{

}