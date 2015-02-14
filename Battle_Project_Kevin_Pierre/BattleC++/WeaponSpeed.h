#pragma once

#include "capacity.h"

class WeaponSpeed : 
	public Capacity
{
	private:
		int _maxValue;

	public:
		~WeaponSpeed(void);

		WeaponSpeed(void);

		void Upgrade();
		void DownGrade();
};

