#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <atomic>

#include "Capacity.h"

#include "Speed.h"
#include "LifePoint.h"
#include "Armor.h"
#include "Regen.h"
#include "WeaponDamage.h"
#include "WeaponRange.h"
#include "WeaponSpeed.h"

#include "Point.h"

/*
	Forward declaration
		--> unsing a static method in the 1st constructor to generate an Ai code randomly
*/
class AI;

//To be sur that every Unit instance will have a distinct id
static std::atomic<int> idCounter = -1;

class Unit
{
	private:
		int _id;				//Unique Identifier od the unit
		std::string _aiCode;	//Behavior of the unit
		Point _position;		//Position in the world
		bool _hasPlayed;		//To know if the unit has already played
		
		/*
			Capacity of the Unit
				--> sub classes of Capacity
		*/
		Speed _speed;
		LifePoint _lifePoint;
		Armor _armor;
		Regen _regen;
		WeaponDamage _weaponDamage;
		WeaponRange _weaponRange;
		WeaponSpeed _weaponSpeed;
		
	public:
		//Destructor
		~Unit(void);

		/*
			First constructor
				--> global level is the level of the unit, global level value will be shared with each capacity randomly
				--> will give an Ai code randomly by calling a static function of AI class (see AI class)
		*/
		Unit(int globalLevel);

		/*
			Second constructor
				--> parameters are all the value to initialize Unit's attributes (its Ai code and all its capacites)
		*/
		Unit(std::string IaCode, int speedLevel, int lifePointLevel, int armorLevel, int regenLevel, int weaponDamageLevel, int weaponRangeLevel, int weaponSpeedLevel);

		//Getter of _id
		const int GetId() const;
		
		/*
			Getter of each Unit's capacities
		*/
		Speed & GetSpeed();
		LifePoint & GetLifePoint();
		Armor & GetArmor();
		Regen & GetRegen();
		WeaponDamage & GetWeaponDamage();
		WeaponRange & GetWeaponRange();
		WeaponSpeed & GetWeaponSpeed();
		
		/*
			Overriding of the bracket ( --> []) operator
				--> Value has to be between 0 and 6 included
				--> Return a reference of the Capacity (will be used as the really class type thanks to inheritance)
		*/
		Capacity & operator [](unsigned int value);

		// Returing the global level of the unit(summing all capacities levels)
		int GetLevel();

		/*
			Getters of the class attributes
				Return _position
				Return _aiCode
				Return _hasPlayed

		*/
		const Point & GetPosition() const;
		const std::string & GetAiCode() const;
		//int GetLevelMaxCap() const;
		bool Unit::GetHasPlayed() const;


		/*
			Regen the LifePoint of the unit with the Regen value's capacity
			And calling the CoolDown method of WeaponSpeed capacity
			(Function used after a full turn of a battle)
		*/
		void Refresh();

		// Setter of _position (2 setters availables)
		void SetPosition(const Point & point);	// with a Point as parameter
		void SetPosition(float x, float y);		// with a x and y coordinates as parameters

		// Setter of the attribute _position (Used to initialized position at the begining of the battle)
		void Unit::SetRandomPosition(const Point & point);

		/* 
			Check if WeaponSpeed _value equal 0 (if the unit can attack) 
				if true --> _value = _maxValue the _hasPlayed = true and return true
				else	--> return false
		*/
		const bool Shoot();

		/*
			Removing LifePoint _value
				The parameter value represente the damage given by an enemy's unit
				The function call ApplyDamage method from LifePoint's capacity 
					--> the parameter passed to LifePoint's function called, is the damage given by the enemy minus the unit's Armor value 
		*/
		void TakeDamage(float value);

		/*
			Check if LifePoint's value of the unit is greather than 0
				return true if LifePoint's value > 0 
				else return false
		*/
		bool IsAlive() const;

		/*
			Check if WeaponSpeed _value equal 0 (if the unit can attack) 
				if true --> return true
				else return false
		*/
		bool CanShoot() const;

		//DownGrade a capacity and Upgrade another capacity
		void Mutate();

		/*
			Find an index of capacity which is not level max
				--> the parameter index is an indx of capacity
				the parameter is an index of capacity not retunrable
		*/
		const int FindCapacity(int index);
		
		/*
			Return a new Unit by "fusing" between 2 units
				--> overriding of the * operator 
		*/
		Unit operator * (Unit & unit);

		//Set lifePoint of an Unit to 0
		void Seppuku();
};

#endif
