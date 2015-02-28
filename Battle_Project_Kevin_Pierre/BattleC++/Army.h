#ifndef ARMY_H
#define ARMY_H

#include <vector>
#include <iostream>

#include "Unit.h"

class Army
{
	//Unit* is a pointer --> for the next semester

	private:
		//Vector containing all the Units of the Army
		std::vector< Unit * > _units;
		int _score;

	public:
		//Destructor
		~Army(void);

		/*
			First Constructor
				Need the number of Unit in the army and the globalLevel for every Unit
		*/
		Army(int nbUnit, int globalLevel);

		/*
			Second Constructor
				Copy the vector in parameter
		*/
		Army(std::vector< Unit * > & units);

		//Getter of _units
		std::vector< Unit * > GetUnitsList();

		//Return an unit from _units who has the id in parameter
		Unit & GetUnit(int id);

		//Return the size of the vector _units
		const int Size() const;

		/*
			Function returning the nearest and the farthest from a point 
			By look the distance between the point and the position of every units in _units
		*/
		Unit & GetNearestUnit(const Point & point);
		Unit & GetFarthestUnit(const Point & point);
		
		/*
			Function returning the lowest and the highest according to the parameter which represente the index of a Unit's capacity 
			By look the level of every units in _units
		*/
		Unit & GetLowestUnit(int indexCapacity);
		Unit & GetHighestUnit(int indexCapacity);

		/*
			Looking for a unit who is have a LifePoint's value equal 0
			If an unit !IsAlive --> removing this unit from the vector _units
		*/
		void Purge();

		//Apply Refresh() on all units --> see class Unit (function called after the end of a turn)
		void Refresh();

		/*
			Replace one unit by an other one generated randomly
			Or
			Mutating a part of the army
		*/
		void Mutate();

		//Add a new Unit randomly generated in the army
		void AddNewUnit(int globalLevel);

		/*
			Mutation bewteen two Army --> Returning a new army composed with :
				--> a part of armyA's units
				--> a part of armyB's units
				--> units to fill the empty space by using the * operator between one unit from ArmyA and one unit from ArmyB randomly chosen
		*/
		Army operator * (const Army & army) const;

		/*
			Overinding of the comparisons operators for ordering
		*/
		bool operator < (const Army & army) const;
		bool operator > (const Army & army) const;
		bool operator >= (const Army & army) const;
		bool operator <= (const Army & army)const;
		bool operator == (const Army & army) const;
		bool operator != (const Army & army) const;
		
		/*
			Getter of the attribute _score
			Setters of the attribute _score
		*/
		int GetScore() const;
		void SetScore(const int score);
		void AddScore(const int scoreToAdd);
		void ResetScore();

		//Return true if at least one unit can play
		bool CanPlay() const;

		//Kill every unit of the army --> called when a battle is lasting more than 3000 turns
		void Kill();
};

#endif
