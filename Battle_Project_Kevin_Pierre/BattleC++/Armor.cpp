#include "Armor.h"

//Destructor
Armor::~Armor(void)
{
}

/*
	Constructor
	Call the base class constructor (Capacity()) 
	And  compute the attribute _value according to the redefinition of the method recomputeValue in its own class
*/
Armor::Armor(void)
	:Capacity()
{
	this->ComputeValue();
}

//Overriding of the method from the base class that compute the _value attribut according to _level
void Armor::ComputeValue()
{
	this->_value = this->_level / 2.f;
}

/*
	Incrementation of _level
	Implementation of the base class function by calling the function on base class 
	And using its own implementation of ComputeValue to set _value
*/
void Armor::Upgrade()
{
	Capacity::Upgrade();
	this->ComputeValue();
}


/*
	Decrementation of _level
	Implementation of the base class function by calling the function on base class
	And using its own implementation of ComputeValue to set _value
*/
void Armor::DownGrade()
{
	Capacity::DownGrade();
	this->ComputeValue();
}

/*
	Setter of _level
	Calling the base class function 
	And using its own implementation of ComputeValue to set _value
*/
void Armor::SetLevel(int level)
{
	Capacity::SetLevel(level);
	this->ComputeValue();
}
