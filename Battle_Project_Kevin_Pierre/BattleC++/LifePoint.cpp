#include "LifePoint.h"


//Destructeur
LifePoint::~LifePoint(void)
{
	
}

//Constructeur
LifePoint::LifePoint(void)
	:Capacity()
{
	this->Upgrade();
	this->_value = (float)this->_maxValue;
}


void LifePoint::Upgrade()
{
	//++(this->_level);
	this->_maxValue = (1 + this->_level) * 10;
}

void LifePoint::DownGrade()
{
	//--(this->_level);
	this->_maxValue = (1 + this->_level) * 10;
}