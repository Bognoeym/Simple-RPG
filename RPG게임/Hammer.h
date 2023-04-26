#pragma once
#include "Weapon.h"

class Hammer : public Weapon
{
public:
	Hammer();
	Hammer(Weapon* tmp);
	int SpecialAttack();
};

