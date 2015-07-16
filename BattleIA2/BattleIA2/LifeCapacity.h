#pragma once

#include "Capacity.h"

//Class representing the life capacity of an unit
class LifeCapacity : public Capacity
{
	private:
		float _maxLife;

		void updateValue()
		{
			_maxLife = static_cast<float>(10.0f * (_level + 1.0f));
			_value = _maxLife;
		}

	public:
		LifeCapacity() : Capacity(0)
		{
			updateValue();
		}

		//Decrease the life value
		bool takeDamage(float damageValue)
		{
			_value -= damageValue;
			return (_value > 0.0f);
		}

		//Return true if still have life, false otherwise
		bool isAlive() const
		{
			return (_value > 0.0f);
		}

		//Increase the life value
		void takeRegen(float regenValue)
		{
			_value += regenValue;
			if (_value > _maxLife) _value = _maxLife;
		}
};

