#pragma once

#include "Capacity.h"

//Class representing the range capacity of an unit
class RangeCapacity : public Capacity
{
	private:
		void updateValue()
		{
			_value = static_cast<float>((2.0f * _level) + 10.0f);
		}

	public:
		RangeCapacity() : Capacity(0)
		{
			updateValue();
		}
};