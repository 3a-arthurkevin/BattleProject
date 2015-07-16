#pragma once

#include "Capacity.h"

//Class representing the armor capacity of an unit
class ArmorCapacity : public Capacity
{
	private:
		void updateValue()
		{
			_value = static_cast<float>(_level * 0.5f);
		}

	public:
		ArmorCapacity() : Capacity(0)
		{
			updateValue();
		}
};


