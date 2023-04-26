#include "Dagger.h"


Dagger::Dagger()
{

}

Dagger::Dagger(Weapon* tmp)
{
	m_iAttackPoint = tmp->GetAttack();
	m_iPrice = tmp->GetPrice();
	m_sWPName = tmp->GetName();
	m_sWPType = tmp->GetType();
}

int Dagger::SpecialAttack()
{
	int attack;
	attack = m_iAttackPoint * 2;
	RED
		MapDrawManager.DrawMidText("크리티컬!!(Damager : " + to_string(attack) + ")", WIDTH, HEIGHT * 0.5 - 1);
	ORIGINAL
		return attack;
}