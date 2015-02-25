#ifndef LIFEPOINT_H
#define LIFEPOINT_H

#include "capacity.h"

/*
	Classe that inherits from Capacity
*/

class LifePoint  : 
	public Capacity
{
	private :
		/*
			Attribute used to save the max LifePoint value
				--> Current lifePoint value is the attribute _value in base class
		*/
		float _maxValue;

	public:
		//Destructor
		~LifePoint(void);

		//Constructor
		LifePoint(void);

		/*
			Compute _maxValue according to _level
			Overriding of function from base class
		*/
		void ComputeValue();

		/*
			Incrementation and Decrementation of _level
			Functions using the definition in base class and adding its own logic after (for (re)compute _maxValue)
		*/
		void Upgrade();
		void DownGrade();

		/*
			Setter of _level
			Function using the definition in base class and adding its own logic after (for (re)compute _maxValue)
		*/
		void SetLevel(int level);

		//Getter of _maxValue
		const float GetMaxValue() const;

		/*
			Function adding life points to _value (according to the unit's regen capacity value --> see Unit class)
				--> _value has to be smaller or equal to _maxValue
		*/
		void RegenLife(float regen);

		/*
			Function removing life points to _value (according to an enemy's weapon damage value --> see Unit and Army class)
			--> _value has to be smaller or equal to _maxValue
		*/
		void ApplyDamage(float damage);

		/*
			_value = _maxValue 
			(used when Unit constructor id called in the case when he has some level its LifePoint's capacity --> see Unit class constructor)
		*/
		void RegenMax();
};

#endif