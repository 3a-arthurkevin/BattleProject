#pragma once

#include "capacity.h"

class LifePoint  : 
	public Capacity
{
	private :
		int _maxValue;

	public:
		~LifePoint(void);

		LifePoint(void);

		virtual void Upgrade();
		virtual void DownGrade();
};

