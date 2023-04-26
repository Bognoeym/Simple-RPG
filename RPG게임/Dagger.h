#pragma once
#include "Weapon.h"

class Dagger : public Weapon
{
public:
	Dagger();
	Dagger(Weapon* tmp);
	int SpecialAttack();
};

