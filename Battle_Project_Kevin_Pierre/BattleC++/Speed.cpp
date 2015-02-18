#include "StdAfx.h"
#include "Speed.h"

Speed::~Speed(void)
{
}

Speed::Speed(void)
	:Capacity()
{
	this->_level = 0;
	this->ComputeValue();
}

void Speed::ComputeValue()
{
	this->_value = 1.f + this->_level;
}

void Speed::Upgrade()
{
	Capacity::Upgrade();
	this->ComputeValue();
}

void Speed::DownGrade()
{
	Capacity::DownGrade();
	this->ComputeValue();
}

void Speed::SetLevel(int level)
{
	Capacity::SetLevel(level);
	this->ComputeValue();
}