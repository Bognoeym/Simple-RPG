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
	if (str == "Ȱ")
		playerWeapon = new Bow(tmp);
	else if (str == "���")
		playerWeapon = new Dagger(tmp);
	else if (str == "��")
		playerWeapon = new Gun(tmp);
	else if (str == "���")
		playerWeapon = new Sword(tmp);
	else if (str == "������")
		playerWeapon = new Wand(tmp);
	else if (str == "�ظ�")
		playerWeapon = new Hammer(tmp);

	m_bHasWeapon = true;
}

void Player::WeaponInfo(int height)
{
	if (m_bHasWeapon)
	{
		MapDrawManager.DrawMidText("����Ÿ�� : " + playerWeapon->GetType() + " �����̸� : " + playerWeapon->GetName()
			+ " ���ݷ� : " + to_string(playerWeapon->GetAttack()), WIDTH, height);
	}
}