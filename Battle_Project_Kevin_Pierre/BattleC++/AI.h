#ifndef AI_H
#define AI_H

#include <vector>
#include <map>
#include <string>

#include "Army.h"
#include "Action.h"
#include "ActionType.h"
#include "Circle.h"

const std::vector< std::string > firstCharVector = { "L", "H" };
const std::vector< std::string > secondCharVector = { "0", "1", "2", "3", "4", "5", "6", "D" };

class AI
{
	public:

		//Destructeur
		~AI(void);

		//Constructeur
		AI(void);
		
		/*
			Functor returning what a Unit from armyA will do against armyB according to Unit's Ai code

					If unit can shoot 
						If an enemy is in weapon range (according to its Ai code)
							Get the vector of all enemies in weapon range and get the enemy to shoot according to the unit's Ai code
							Return an Action with actionType::Shoot with the id of the enemy
						Else (no enemy in weapon range)
							Get the nearest enemy according to unit's Ai code
							Return Action with ActionType::Move with the position of the enemy / id of the enemy
					Else (can't shoot)
						Get the nearest enemy from Unit
						If Unit is in weapon range of the nearst enemy
							Move to the opposite direction from the enemy
							return Action with actionType::Flee and position of the enemy and id of the enemy
						Else (not in weapon range)
							Return action with ActionType::None
		*/
		const Action operator()(Unit & unit, Army & armyA, Army & armyB) const;
		
		/*
			Check if an enemy from the other army is in the range from a point
				--> range can be the Speed or the WeaponRange'value of a Unit
				--> point is the position of the Unit
				--> unitsB is the vector of Units to defeat
			Return true if an enemy is in range
			else return false
		*/
		bool EnemyInRange(const float range, const Point & point, std::vector<Unit*> & unitsB) const;
		
		/*
			Return a vector of Unit* containing all the enemies in the range a Unit's range from its position
				--> range can be the Speed or the WeaponRange'value of a Unit
				--> point is the position of the Unit
				--> unitsB is the vector of Units to defeat
		*/
		std::vector<Unit*> AI::GetEnemiesInRange(float range, const Point & point, std::vector<Unit*> & unitsB) const;
		
		/*
			Return the nearest enemy from a Unit's position
			--> point is the position of the Unit
			--> unitsB is the vector of Units to defeat
		*/
		Unit & GetNearestEnemy(const Point & point, std::vector<Unit*> & unitsB) const;
		
		/*
			Return the farthest enemy from a Unit's position
				--> point is the position of the Unit
				--> unitsB is the vector of Units to defeat
		*/
		Unit & GetFarthestEnemy(const Point & point, std::vector<Unit*> & unitsB) const;
		
		/*
			Return the enemy with the lowest value of a specific capacity
			--> indexCapacity is the index of the capacity to check (checking by using the overrided operator [] in see class Unit)
			--> unitsB is the vector of Units to defeat
		*/
		Unit & GetLowestEnemy(unsigned int indexCapacity, std::vector<Unit*> & unitsB) const;
		
		/*
			Return the enemy with the highest value of a specific capacity
				--> indexCapacity is the index of the capacity to check (checking by using the overrided operator [] in see class Unit)
				--> unitsB is the vector of Units to defeat
		*/
		Unit & GetHighestEnemy(unsigned int indexCapacity, std::vector<Unit*> & unitsB) const;
		
		//Return a randomly generated Ai code for a unit
		static const std::string GetRandomAiCode();
};

#endif