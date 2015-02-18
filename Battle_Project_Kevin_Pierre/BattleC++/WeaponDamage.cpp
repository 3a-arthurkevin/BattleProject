#include "WeaponDamage.h"

WeaponDamage::~WeaponDamage(void)
{
}


WeaponDamage::WeaponDamage(void)
	:Capacity()
{
	this->ComputeValue();
}


void WeaponDamage::ComputeValue()
{
	this->_value = (1 + this->_level) * 1.5f;
}

void WeaponDamage::Upgrade()
{
	Capacity::Upgrade();
	this->ComputeValue();

}

void WeaponDamage::DownGrade()
{
	Capacity::DownGrade();
	this->ComputeValue();
}

void WeaponDamage::SetLevel(int level)
{
	Capacity::SetLevel(level);
	this->ComputeValue();
}