#include "Capacity.h"

//Destructor
Capacity::~Capacity(void)
{
}

//Constructor - Setting attributes at 0 (default value)
Capacity::Capacity(void)
{
	this->_level = 0;
	this->_value = 0.f;
}

//Function that will be redefined in sub classes
void Capacity::ComputeValue() 
{
}

//Incrementation of level and recompute the value with the new level 
void Capacity::Upgrade()
{
	++(this->_level);
}

//Decrementation of level and recompute the value with the new level 
void Capacity::DownGrade()
{
	--(this->_level);
}

//Getter of _level attribute
const int Capacity::GetLevel() const
{
	return this->_level;
}

//Getter of _value attribute
const float Capacity::GetValue() const
{
	return this->_value;
}

//Setter of _level attribute
void Capacity::SetLevel(int level)
{
	this->_level = level;
}