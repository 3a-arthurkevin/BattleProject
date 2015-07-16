#pragma once

#include "Capacity.h"

//Class representing the speed capactiy of an unit
class SpeedCapacity : public Capacity
{
	private:
		void updateValue()
		{
			_value = static_cast<float>(_level + 1.0f);
		}

	public:
		SpeedCapacity() : Capacity(0)
		{
			updateValue();
		}
};

