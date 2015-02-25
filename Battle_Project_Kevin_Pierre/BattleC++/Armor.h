#ifndef ARMOR_H
#define ARMOR_H

#include "capacity.h"

/*
	Classe that inherits from Capacity
*/

class Armor : public Capacity
{
	public:
		//Destructor
		~Armor(void);

		//Constructor
		Armor(void);

		/*
			Compute _value according to _level
			Overriding of function from base class
		*/
		void ComputeValue();

		/*
			Incrementation and Decrementation of _level
			Functions using the definition in base class and adding its own logic after (for (re)compute _value)
		*/
		void Upgrade();
		void DownGrade();

		/*
			Setter of _level
			Function using the definition in base class and adding its own logic after (for (re)compute _value)
		*/
		void SetLevel(int level);
};

#endif