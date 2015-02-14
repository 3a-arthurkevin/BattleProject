#pragma once

#include "capacity.h"

class WeaponRange :
	public Capacity
{
	public:
		~WeaponRange(void);

		WeaponRange(void);

		void Upgrade();
		void DownGrade();
};

