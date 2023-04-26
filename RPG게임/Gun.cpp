#include "Gun.h"


Gun::Gun()
{

}

Gun::Gun(Weapon* tmp)
{
	m_iAttackPoint = tmp->GetAttack();
	m_iPrice = tmp->GetPrice();
	m_sWPName = tmp->GetName();
	m_sWPType = tmp->GetType();
}

int Gun::SpecialAttack()
{
	int attack, randNum;
	attack = m_iAttackPoint * 3;
	randNum = rand() % 2;  // 1/2

	if (randNum == 1)
	{
		RED
			MapDrawManager.DrawMidText("Miss!(Damager : 0 )", WIDTH, HEIGHT * 0.5 - 1);
		ORIGINAL
			return 0;
	}
	RED
		MapDrawManager.DrawMidText("Çìµå¼¦!!(Damager : " + to_string(attack) + ")", WIDTH, HEIGHT * 0.5 - 1);
	ORIGINAL
	return attack;
}