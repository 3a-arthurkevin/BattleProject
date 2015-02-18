#include "StdAfx.h"
#include "WeaponRange.h"

WeaponRange::~WeaponRange(void)
{
}

WeaponRange::WeaponRange(void)
	:Capacity()
{
	this->ComputeValue();
}

void WeaponRange::ComputeValue()
{
	this->_value = 10.f + (this->_level * 2.f);
}

void WeaponRange::Upgrade()
{
	Capacity::Upgrade();
	this->ComputeValue();
}

void WeaponRange::DownGrade()
{
	Capacity::DownGrade();
	this->ComputeValue();
}

void WeaponRange::SetLevel(int level)
{
	Capacity::SetLevel(level);
	this->ComputeValue();
}