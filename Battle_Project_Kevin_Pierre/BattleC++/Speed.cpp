#include "Speed.h"

//Destructor
Speed::~Speed(void)
{
}

/*
	Constructor
	Call the base class constructor (Capacity())
	And  compute the attribute _value according to the redefinition of the method recomputeValue in its own class
*/
Speed::Speed(void)
	:Capacity()
{
	this->_level = 0;
	this->ComputeValue();
}

//Overriding of the method from the base class that compute the _value attribut according to _level
void Speed::ComputeValue()
{
	this->_value = 1.f + this->_level;
}

/*
	Incrementation of _level
	Implementation of the base class function by calling the function on base class
	And using its own implementation of ComputeValue to set _value
*/
void Speed::Upgrade()
{
	Capacity::Upgrade();
	this->ComputeValue();
}

/*
	Decrementation of _level
	Implementation of the base class function by calling the function on base class
	And using its own implementation of ComputeValue to set _value
*/
void Speed::DownGrade()
{
	Capacity::DownGrade();
	this->ComputeValue();
}

/*
	Setter of _level
	Calling the base class function
	And using its own implementation of ComputeValue to set _value
*/
void Speed::SetLevel(int level)
{
	Capacity::SetLevel(level);
	this->ComputeValue();
}