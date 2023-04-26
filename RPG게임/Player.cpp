#include "Player.h"

Player::Player()
{
	m_bHasWeapon = false;
}

void Player::RockScisPaper()
{
	char ch = getch();

	switch (ch)
	{
	case '1':
		m_iRSP = SCISSORS;
		break;

	case '2':
		m_iRSP = ROCK;
		break;

	case '3':
		m_iRSP = PAPER;
		break;
	}
}

void Player::SetWeapon(Weapon* tmp)
{
	string str = tmp->GetType();
	if (str == "활")
		playerWeapon = new Bow(tmp);
	else if (str == "대거")
		playerWeapon = new Dagger(tmp);
	else if (str == "총")
		playerWeapon = new Gun(tmp);
	else if (str == "장검")
		playerWeapon = new Sword(tmp);
	else if (str == "지팡이")
		playerWeapon = new Wand(tmp);
	else if (str == "해머")
		playerWeapon = new Hammer(tmp);

	m_bHasWeapon = true;
}

void Player::WeaponInfo(int height)
{
	if (m_bHasWeapon)
	{
		MapDrawManager.DrawMidText("무기타입 : " + playerWeapon->GetType() + " 무기이름 : " + playerWeapon->GetName()
			+ " 공격력 : " + to_string(playerWeapon->GetAttack()), WIDTH, height);
	}
}