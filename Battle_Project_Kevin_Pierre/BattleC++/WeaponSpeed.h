#ifndef WEAPONSPEED_H
#define WEAPONSPEED_H

#include "capacity.h"

/*
	Classe that inherits from Capacity
*/

class WeaponSpeed : 
	public Capacity
{
	private:
		/*
			Attribute used to save the max time between each attack
				--> Current value is the attribute _value in base class

			Detail about the WeaponSpeed Capacity in Unit class
				Unit class can attack if WeaponSpeed's _value = 0
				When unit just attacked an enemy --> _value = _maxValue
				And for each turn, _value is decremented until _value = 0;
		*/
		float _maxValue;

	public:
		//Destructor
		~WeaponSpeed(void);

		//Constructor
		WeaponSpeed(void);

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

		//Decremente _value (function called after each unit's action expect when unit has attacked an enemy)
		void CoolDown();

		//Set _value = _maxValue (function called when unit has attacked an enemy)
		void WeaponUsed();
};

#endif