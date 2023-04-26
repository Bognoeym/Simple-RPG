#include "Sword.h"


Sword::Sword()
{

}

Sword::Sword(Weapon* tmp)
{
	m_iAttackPoint = tmp->GetAttack();
	m_iPrice = tmp->GetPrice();
	m_sWPName = tmp->GetName();
	m_sWPType = tmp->GetType();
}

int Sword::SpecialAttack()
{
	int attack;
	attack = m_iAttackPoint * 2;
	RED
		MapDrawManager.DrawMidText("°Ë±â!!(Damager : " + to_string(attack) + ")", WIDTH, HEIGHT * 0.5 - 1);
	ORIGINAL
		return attack;
}