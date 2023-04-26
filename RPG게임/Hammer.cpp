#include "Hammer.h"


Hammer::Hammer()
{

}

Hammer::Hammer(Weapon* tmp)
{
	m_iAttackPoint = tmp->GetAttack();
	m_iPrice = tmp->GetPrice();
	m_sWPName = tmp->GetName();
	m_sWPType = tmp->GetType();
}

int Hammer::SpecialAttack()
{
	int attack, randNum;
	attack = m_iAttackPoint * 2;
	randNum = rand() % 3;

	if (randNum == 1)
	{
		attack = m_iAttackPoint * 4;  // 4배
		RED
			MapDrawManager.DrawMidText("!!po내려치기wer!!(Damager : " + to_string(attack) + ")", WIDTH, HEIGHT * 0.5 - 1);
		ORIGINAL
	}
	else
	{
		RED
			MapDrawManager.DrawMidText("내려치기!!(Damager : " + to_string(attack) + ")", WIDTH, HEIGHT * 0.5 - 1);
		ORIGINAL
	}
		return attack;
}