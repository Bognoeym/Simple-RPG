#pragma once
#include "Weapon.h"

class Sword : public Weapon
{
public:
	Sword();
	Sword(Weapon* tmp);
	int SpecialAttack();
};

