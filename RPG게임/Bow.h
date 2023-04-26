#pragma once
#include "Weapon.h"

class Bow : public Weapon
{
public:
	Bow();
	Bow(Weapon* tmp);
	int SpecialAttack();
};

