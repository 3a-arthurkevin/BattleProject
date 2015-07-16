#pragma once

#include "Capacity.h"

//Class representing the damage capacity of an unit
class DamageCapacity : public Capacity
{
	private:
		void updateValue()
		{
			_value = static_cast<float>(1.5f * (_level + 1.0f));
		}

	public:
		DamageCapacity() : Capacity(0)
		{
			updateValue();
		}
};

