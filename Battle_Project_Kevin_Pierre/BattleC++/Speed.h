#ifndef SPEED_H
#define SPEED_H

#include "capacity.h"

/*
	Classe that inherits from Capacity
*/

class Speed  : 
	public Capacity
{
	public:
		//Destructor
		~Speed(void);

		//Constructor
		Speed(void);

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