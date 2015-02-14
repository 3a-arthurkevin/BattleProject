#include "Capacity.h"


Capacity::~Capacity(void)
{
}

Capacity::Capacity(void)
{
	this->_level = 0;
}

const int Capacity::GetLevel() const
{
	return this->_level;
}

const float Capacity::GetValue() const
{
	return this->_value;
}