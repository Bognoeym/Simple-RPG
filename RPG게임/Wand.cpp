#include "Wand.h"

Wand::Wand()
{

}

Wand::Wand(Weapon* tmp)
{
	m_iAttackPoint = tmp->GetAttack();
	m_iPrice = tmp->GetPrice();
	m_sWPName = tmp->GetName();
	m_sWPType = tmp->GetType();
}

int Wand::SpecialAttack()
{
	int attack, randNum, heal;
	attack = m_iAttackPoint * 3;
	heal = 5;
	randNum = rand() % 3;  // 1/3

	if (randNum == 1)
	{
		RED
			MapDrawManager.DrawMidText("Miss!(Damager : 0 )", WIDTH, HEIGHT * 0.5 - 1);
		ORIGINAL
			return 0;
	}
	else if (randNum == 2)
	{
		RED
			MapDrawManager.DrawMidText("치유!(Health Point : 5 )", WIDTH, HEIGHT * 0.5 - 1);
		ORIGINAL
			return heal;
	}
	else
	{
		RED
			MapDrawManager.DrawMidText("즉사!!(Damager : " + to_string(attack) + ")", WIDTH, HEIGHT * 0.5 - 1);
		ORIGINAL
			return attack;
	}
}