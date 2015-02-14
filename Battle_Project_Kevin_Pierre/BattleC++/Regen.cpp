#include "StdAfx.h"
#include "Regen.h"

Regen::~Regen(void)
{
}

Regen::Regen(void)
	:Capacity()
{
	this->Upgrade();
}


void Regen::Upgrade()
{
	this->_value = this->_level * 3;
}

void Regen::DownGrade()
{
	this->_value = this->_level * 3;
}