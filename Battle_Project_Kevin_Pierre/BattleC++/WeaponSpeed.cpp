#include "StdAfx.h"
#include "WeaponSpeed.h"

WeaponSpeed::~WeaponSpeed(void)
{
}

WeaponSpeed::WeaponSpeed(void)
	:Capacity()
{
	this->ComputeValue();
	this->_value = 0;
}

void WeaponSpeed::ComputeValue()
{
	this->_maxValue = 1000.f / (1 + this->_level);
}

void WeaponSpeed::Upgrade()
{
	Capacity::Upgrade();
	this->ComputeValue();
}

void WeaponSpeed::DownGrade()
{
	Capacity::DownGrade();
	this->ComputeValue();
}

void WeaponSpeed::SetLevel(int level)
{
	Capacity::SetLevel(level);
	this->ComputeValue();
}

const float WeaponSpeed::GetMaxValue() const
{
	return this->_maxValue;
}

void WeaponSpeed::CoolDown()
{
	if (this->_value > 0)
		--(this->_value);
}

void WeaponSpeed::WeaponUsed()
{
	this->_value = this->_maxValue;
}