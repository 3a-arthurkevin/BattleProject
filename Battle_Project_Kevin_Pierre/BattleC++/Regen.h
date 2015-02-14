#pragma once

#include "capacity.h"

class Regen : 
	public Capacity
{
	public:
		~Regen(void);

		Regen(void);

		void Upgrade();
		void DownGrade();
};

