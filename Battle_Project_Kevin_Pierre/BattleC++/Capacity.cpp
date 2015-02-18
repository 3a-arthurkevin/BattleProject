#include "Capacity.h"

#include <iostream>

Capacity::~Capacity(void)
{
}

Capacity::Capacity(void)
{
	this->_level = 0;
}

void Capacity::ComputeValue() 
{
}

void Capacity::Upgrade()
{
	++(this->_level);
	this->ComputeValue();
}

void Capacity::DownGrade()
{
	--(this->_level);
	this->ComputeValue();
}


const int Capacity::GetLevel() const
{
	return this->_level;
}

const float Capacity::GetValue() const
{
	return this->_value;
}

void Capacity::SetLevel(int level)
{
	this->_level = level;
	this->ComputeValue();
}