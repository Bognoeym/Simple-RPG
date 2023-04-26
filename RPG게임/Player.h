#pragma once
#include "Character.h"
#include "Weapon.h"
#include "Bow.h"
#include "Dagger.h"
#include "Gun.h"
#include "Sword.h"
#include "Wand.h"
#include "Hammer.h"

class Player : public Character
{
private:
	Weapon* playerWeapon;
	bool m_bHasWeapon;
public:
	Player();
	inline void SetName(string name) { m_sName = name; }
	inline bool GetHasWeapon() { return m_bHasWeapon; }
	void SetWeapon(Weapon* weapon);
	Weapon* GetWeapon() { return playerWeapon; }
	void RockScisPaper();
	void WeaponInfo(int height);
};