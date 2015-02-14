#include "StdAfx.h"
#include "WeaponSpeed.h"

WeaponSpeed::~WeaponSpeed(void)
{
}

WeaponSpeed::WeaponSpeed(void)
	:Capacity()
{
	this->Upgrade();
	this->_value = 0;
}


void WeaponSpeed::Upgrade()
{
	this->_maxValue = 1000 / (1 + this->_level);
}

void WeaponSpeed::DownGrade()
{
	this->_maxValue = 1000 / (1 + this->_level);
}
