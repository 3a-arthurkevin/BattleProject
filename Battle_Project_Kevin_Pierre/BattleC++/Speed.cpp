#include "StdAfx.h"
#include "Speed.h"

Speed::~Speed(void)
{
}

Speed::Speed(void)
	:Capacity()
{
	this->Upgrade();
}


void Speed::Upgrade()
{
	this->_level = 1 + this->_level;
}

void Speed::DownGrade()
{
	this->_level = 1 + this->_level;
}
