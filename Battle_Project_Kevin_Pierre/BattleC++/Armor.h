#pragma once

#include "capacity.h"

class Armor : public Capacity
{
	public:
		~Armor(void);

		Armor(void);

		void Upgrade();
		void DownGrade();
};

