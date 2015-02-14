#include "Damage.h"

Damage::~Damage(void)
{
}


Damage::Damage(void)
	:Capacity()
{
	this->Upgrade();
}




void Damage::Upgrade()
{
	this->_value = (1 + this->_level) * 1.5f;
}

void Damage::DownGrade()
{
	this->_value = (1 + this->_level) * 1.5f;
}
