#pragma once
#include "Weapon.h"

class Gun : public Weapon
{
public:
	Gun();
	Gun(Weapon* tmp);
	int SpecialAttack();
};

