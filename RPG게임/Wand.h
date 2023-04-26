#pragma once
#include "Weapon.h"

class Wand : public Weapon
{
public:
	Wand();
	Wand(Weapon* tmp);
	int SpecialAttack();
};

