#include "Monster.h"

Monster::Monster()
{

}

void Monster::RockScisPaper()
{
	int rsp;
	rsp = rand() % 3 + 1;
	m_iRSP = rsp;
}