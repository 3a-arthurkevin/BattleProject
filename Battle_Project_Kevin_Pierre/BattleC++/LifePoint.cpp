#include "LifePoint.h"


//Destructeur
LifePoint::~LifePoint(void)
{
	
}

//Constructeur
LifePoint::LifePoint(void)
	:Capacity()
{
	this->ComputeValue();
	this->_value = this->_maxValue;
}

void LifePoint::ComputeValue()
{
	this->_maxValue = (1 + this->_level) * 10.f;
}

void LifePoint::Upgrade()
{
	Capacity::Upgrade();
	this->ComputeValue();
}
	
void LifePoint::DownGrade()
{
	Capacity::DownGrade();
	this->ComputeValue();
}

void LifePoint::SetLevel(int level)
{
	Capacity::SetLevel(level);
	this->ComputeValue();
}

const float LifePoint::GetMaxValue() const
{
	return this->_maxValue;
}

void LifePoint::RegenLife(float regen)
{
	this->_value += regen;

	if (this->_value > this->_maxValue)
		this->_value = this->_maxValue;
}

void LifePoint::ApplyDamage(float damage)
{
	this->_value -= damage;

	if (this->_value < 0)
		this->_value = 0;
}