#include "Armor.h"

Armor::~Armor(void)
{
}

Armor::Armor(void)
	:Capacity()
{
	this->ComputeValue();
}


void Armor::ComputeValue()
{
	this->_value = this->_level / 2.f;
}

void Armor::Upgrade()
{
	Capacity::Upgrade();
	this->ComputeValue();
}

void Armor::DownGrade()
{
	Capacity::DownGrade();
	this->ComputeValue();
}

void Armor::SetLevel(int level)
{
	Capacity::SetLevel(level);
	this->ComputeValue();
}
