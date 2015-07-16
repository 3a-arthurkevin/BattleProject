#pragma once

#include "Capacity.h"

//Class representing the firerate capacity of an unit
class FirerateCapacity : public Capacity
{
	private:
		float _reloadingTime;

		void updateValue()
		{
			_value = 0.0f;
			_reloadingTime = static_cast<float>(/*1000.0f*/ 10.0f / (_level + 1.0f));
		}

	public:
		FirerateCapacity() : Capacity(0)
		{
			updateValue();
		}

		//set the cooldown to the maximum
		void shoot()
		{
			_value = _reloadingTime;
		}

		//return true if the cooldown is at 0, false otherwise
		bool canShoot() const
		{
			return _value < 0.001f;
		}

		//decrease the cooldown
		void reload()
		{
			_value -= 1.0f;
			if (_value < 0.0f) _value = 0.0f;
		}
};

