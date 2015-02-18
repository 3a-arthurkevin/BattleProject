#include "StdAfx.h"
#include "Regen.h"

Regen::~Regen(void)
{
}

Regen::Regen(void)
	:Capacity()
{
	this->ComputeValue();
}


void Regen::ComputeValue()
{
	this->_value = this->_level / 1000.f;
}

void Regen::Upgrade()
{
	Capacity::Upgrade();
	this->ComputeValue();
}

void Regen::DownGrade()
{
	Capacity::DownGrade();
	this->ComputeValue();
}

void Regen::SetLevel(int level)
{
	Capacity::SetLevel(level);
	this->ComputeValue();
}