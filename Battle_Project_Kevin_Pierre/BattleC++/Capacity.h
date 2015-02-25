#ifndef CAPACITY_H
#define CAPACITY_H

/*
	This class will be use as base class for inheritance of capacities (Speed, LifePoint, etc...)
*/

class Capacity
{

	protected:
		/*
			Class attributes
		*/

		int _level;		// Level of the capacity
		float _value;	// Value of the capacity

	public:
		/*
			Functions
		*/

		//Desctructor
		~Capacity(void);

		//Constructor
		Capacity(void);

		/*
			Compute _value according to a formula (normally used when _level changed)
				--> Virtual as the formula will be defined in the sub class
				--> not a pure Virtual as we will use this class in Unit Class (See Operator[] overriding in Unit class) 
		*/
		virtual void ComputeValue();

		/*
			Functions that increment or decremente the capacity's level and recompute the value according to the new level affected
				--> Virtual because these 2 functions will be completed in Capacity's sub classes by using the existing code and adding their own logic
		*/
		virtual void Upgrade();
		virtual void DownGrade();

		//Getter for this class attributs
		const int GetLevel() const;
		const float GetValue() const;

		/*
			Setter of the _level (and will recompute the _value according to the new level setted in sub classes)
				Virtual as _level will impact _value so _value has to be (re)computed with the sub class method redefinition)
		*/
		virtual void SetLevel(int level);
};

#endif