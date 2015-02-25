#include "LifePoint.h"

//Destructor
LifePoint::~LifePoint(void)
{
	
}

/*
	Constructor
	Call the base class constructor (Capacity())
	And compute the attribute _value according to the redefinition of the method recomputeValue in its own class
	_value = _maxValue (default)
*/
LifePoint::LifePoint(void)
	:Capacity()
{
	this->ComputeValue();
	this->_value = this->_maxValue;
}

//Overriding of the method from the base class that compute _maxValue attribut according to _level
void LifePoint::ComputeValue()
{
	this->_maxValue = (1.f + this->_level) * 10.f;
}

/*
	Incrementation of _level
	Implementation of the base class function by calling the function on base class
	And using its own implementation of ComputeValue to set _value
*/
void LifePoint::Upgrade()
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
void LifePoint::DownGrade()
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
void LifePoint::SetLevel(int level)
{
	Capacity::SetLevel(level);
	this->ComputeValue();
}

//Getter of _maxValue
const float LifePoint::GetMaxValue() const
{
	return this->_maxValue;
}

/*
	Function that add life points to _value (according to the unit's regen capacity value --> see Unit class)
		--> _value is capped because it can't be greater than _maxValue
*/
void LifePoint::RegenLife(float regen)
{
	this->_value += regen;

	if (this->_value > this->_maxValue)
		this->_value = this->_maxValue;
}

/*
	Function removing life points to _value (according to an enemy's weapon damage value --> see Unit and Army class)
	--> _value can't to be smaller than 0
*/
void LifePoint::ApplyDamage(float damage)
{
	this->_value -= damage;

	if (this->_value < 0)
		this->_value = 0;
}

/*
	_value = _maxValue
		Used when Unit constructor is called or when initializing the attributes of a newly created Unit
			--> When Unit Upgrade or Downgrade (see Unit class constructor)
*/
void LifePoint::RegenMax()
{
	this->_value = this->_maxValue;
}