#pragma once

#ifndef ARMOR_CAPACITY_H
#define ARMOR_CAPACITY_H

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

#endif //ARMOR_CAPACITY_H