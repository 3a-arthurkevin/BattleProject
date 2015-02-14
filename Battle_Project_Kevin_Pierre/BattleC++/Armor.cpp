#include "Armor.h"

Armor::~Armor(void)
{
}

Armor::Armor(void)
	:Capacity()
{
	this->Upgrade();
}




void Armor::Upgrade()
{
	this->_value = this->_level * 2.f;
}

void  Armor::DownGrade()
{
	this->_value = this->_level * 2.f;
}
