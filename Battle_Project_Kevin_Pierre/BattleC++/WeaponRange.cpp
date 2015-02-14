#include "StdAfx.h"
#include "WeaponRange.h"

WeaponRange::~WeaponRange(void)
{
}

WeaponRange::WeaponRange(void)
	:Capacity()
{
	this->Upgrade();
}

void WeaponRange::Upgrade()
{
	this->_value = 10.f + (this->_level * 2.f);
}

void WeaponRange::DownGrade()
{
	this->_value = 10.f + (this->_level * 2.f);
}
