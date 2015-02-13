#pragma once

#include "capacity.h"

class LifePoint  : 
	public Capacity
{
	private :
		int lifePointMax;

	public:
		LifePoint(void);
		~LifePoint(void);
};

