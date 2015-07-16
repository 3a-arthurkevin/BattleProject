#pragma once

#include "Capacity.h"

//Class representing the regen capactiy of an unit
class RegenCapacity : public Capacity
{
	private:
		void updateValue()
		{
			_value = static_cast<float>(_level * 0.01f);
		}

	public:
		RegenCapacity() : Capacity(0)
		{
			updateValue();
		}
};

