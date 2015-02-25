#include "WeaponSpeed.h"

//Destructor
WeaponSpeed::~WeaponSpeed(void)
{
}

/*
	Constructor
	Call the base class constructor (Capacity())
	And compute the attribute _value according to the redefinition of the method recomputeValue in its own class
	_value = 0 (default)
*/
WeaponSpeed::WeaponSpeed(void)
	:Capacity()
{
	this->ComputeValue();
	this->_value = 0;
}

//Overriding of the method from the base class that compute _maxValue attribut according to _level
void WeaponSpeed::ComputeValue()
{
	//this->_maxValue = 1000.f / (1.f + this->_level);
	this->_maxValue = 10.f / (1.f + this->_level);
}

/*
	Incrementation of _level
	Implementation of the base class function by calling the function on base class
	And using its own implementation of ComputeValue to set _value
*/
void WeaponSpeed::Upgrade()
{
	Capacity::Upgrade();
	this->ComputeValue();
}

/*
	Decrementation of _level
	Implementation of the base class function by calling the function on base class
	And using its own implementation of ComputeValue to set _value
	Capping _value if it is greater than _maxValue after the downgrade
*/
void WeaponSpeed::DownGrade()
{
	Capacity::DownGrade();
	this->ComputeValue();

	if (this->_value > this->_maxValue)
		this->_value = this->_maxValue;
}

/*
	Setter of _level
	Calling the base class function
	And using its own implementation of ComputeValue to set _value
*/
void WeaponSpeed::SetLevel(int level)
{
	Capacity::SetLevel(level);
	this->ComputeValue();
}

//Getter of _maxValue
const float WeaponSpeed::GetMaxValue() const
{
	return this->_maxValue;
}

//Decremente _value if _value is greater than 0
void WeaponSpeed::CoolDown()
{
	if (this->_value > 0)
		this->_value -= 1;
}

//Set _value = _maxValue
void WeaponSpeed::WeaponUsed()
{
	this->_value = this->_maxValue;
}