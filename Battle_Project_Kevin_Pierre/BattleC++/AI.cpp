#include "AI.h"

AI::~AI(void)
{
}

AI::AI(void)
{
	
}

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
const Action AI::operator()(Unit & unit, Army & armyA, Army & armyB) const
{
	Action actionToDo;
	actionToDo.SetLocation(unit.GetPosition());
	
	std::string firstChar(1, unit.GetAiCode()[0]);
	std::string secondChar(1, unit.GetAiCode()[1]);
	unsigned int secondCharInt = std::atoi(&(unit.GetAiCode()[1])); 

	//Check is unit can shoot
	if (unit.CanShoot())
	{
		//Check if at least one enemy is at weapon range
		if (this->EnemyInRange(unit.GetWeaponRange().GetValue(), unit.GetPosition(), armyB.GetUnitsList()))
		{
			actionToDo.SetAction(ActionType::Shoot);

			std::vector<Unit*> enemiesInRange = this->GetEnemiesInRange(unit.GetWeaponRange().GetValue(), unit.GetPosition(), armyB.GetUnitsList());

			//Set Action according to unit's ai code
			if (firstChar.compare("L") == 0)
			{
				if (secondChar.compare("D") == 0)
				{
					Unit enemyToShoot = this->GetNearestEnemy(unit.GetPosition(), enemiesInRange);
					actionToDo.SetId(enemyToShoot.GetId());
					actionToDo.SetLocation(enemyToShoot.GetPosition());
				}
				else if (secondCharInt >= 0 && secondCharInt <= 6)
				{
					Unit enemyToShoot = this->GetLowestEnemy(secondCharInt, enemiesInRange);
					actionToDo.SetId(enemyToShoot.GetId());
					actionToDo.SetLocation(enemyToShoot.GetPosition());
				}
				else
					std::cout << "Error - 2nd char of ai code unknown" << std::endl;
			}
			else if (firstChar.compare("H") == 0)
			{
				if (secondChar.compare("D") == 0)
				{
					Unit enemyToShoot = this->GetFarthestEnemy(unit.GetPosition(), enemiesInRange);
					actionToDo.SetId(enemyToShoot.GetId());
					actionToDo.SetLocation(enemyToShoot.GetPosition());
				}
				else if (secondCharInt >= 0 && secondCharInt <= 6)
				{
					Unit enemyToShoot = this->GetHighestEnemy(secondCharInt, enemiesInRange);
					actionToDo.SetId(enemyToShoot.GetId());
					actionToDo.SetLocation(enemyToShoot.GetPosition());
				}
				else
					std::cout << "Error - 2nd char of ai code unknown" << std::endl;
			}
			else
				std::cout << "Error - 1st char of ai code unknown" << std::endl;
		}
		//Moving to the nearest enemy
		else
		{
			Unit nearestEnemy = armyB.GetNearestUnit(unit.GetPosition());
			actionToDo.SetAction(ActionType::Move);

			actionToDo.SetId(nearestEnemy.GetId());

			float distanceBetweenUnits = unit.GetPosition().Distance(nearestEnemy.GetPosition());

			if (distanceBetweenUnits > 1.f || distanceBetweenUnits < -1.f)
			{
				float k = (unit.GetSpeed().GetValue() / distanceBetweenUnits);
				Point pUnit(unit.GetPosition());
				Point pEnemy(nearestEnemy.GetPosition());

				Point directionalVector(pEnemy - pUnit);

				actionToDo.SetLocation(unit.GetPosition() + (directionalVector * k));
			}
		}
	}
	//Flee
	else
	{
		actionToDo.SetAction(ActionType::Flee);

		Unit nearestEnemy = armyB.GetNearestUnit(unit.GetPosition());

		if ((nearestEnemy.GetPosition().Distance(unit.GetPosition())) < nearestEnemy.GetWeaponRange().GetValue())
		{
			float distanceBetweenUnits = unit.GetPosition().Distance(nearestEnemy.GetPosition());

			if (distanceBetweenUnits > 1.f || distanceBetweenUnits < -1.f)
			{
				float k = (unit.GetSpeed().GetValue() / distanceBetweenUnits);
				Point pUnit(unit.GetPosition());
				Point pEnemy(nearestEnemy.GetPosition());

				Point directionalVector(pEnemy - pUnit);

				actionToDo.SetLocation(unit.GetPosition() + (directionalVector * -k));
			}
		}
	}
	
	return actionToDo;
}

/*
	Check if an enemy from the other army is in the range from a point
		--> range can be the Speed or the WeaponRange'value of a Unit
		--> point is the position of the Unit
		--> armyB is the Army, Unit has to defeat
	Return true if an enemy is in range
	else return false
*/
bool AI::EnemyInRange(const float range, const Point & point, std::vector<Unit*> & unitsB) const
{
	Circle circlularRange(point, range);

	unsigned int indexArmyB;
	unsigned int sizeArmyB = unitsB.size();

	for (indexArmyB = 0; indexArmyB < sizeArmyB; ++indexArmyB)
	{
		if (circlularRange.Include(unitsB[indexArmyB]->GetPosition()))
			return true;
	}
	return false;
}

/*
	Return a vector of Unit* containing all the enemies in the range a Unit's range from its position
		--> range can be the Speed or the WeaponRange'value of a Unit
		--> point is the position of the Unit
		--> unitsB is the vector of Units to defeat
*/
std::vector<Unit*> AI::GetEnemiesInRange(float range, const Point & point, std::vector<Unit*> & unitsB) const
{
	std::vector<Unit*> enemiesInRange;
	Circle circlularRange(point, range);

	unsigned int indexArmyB;
	unsigned int sizeArmyB = unitsB.size();

	for (indexArmyB = 0; indexArmyB < sizeArmyB; ++indexArmyB)
	{
		if (circlularRange.Include(unitsB[indexArmyB]->GetPosition()))
			enemiesInRange.push_back(unitsB[indexArmyB]);
	}

	return enemiesInRange;
}

/*
	Return the nearest enemy from a Unit's position
		--> point is the position of the Unit
		--> unitsB is the vector of Units to defeat
*/
Unit & AI::GetNearestEnemy(const Point & point, std::vector<Unit*> & unitsB) const
{
	int indexNearest = 0;
	float shortestDistance = point.Distance(unitsB[indexNearest]->GetPosition());

	unsigned int index;
	unsigned int size = unitsB.size();

	for (index = 1; index < size; ++index)
	{
		if (point.Distance((unitsB[index])->GetPosition()) < shortestDistance)
		{
			indexNearest = index;
			shortestDistance = point.Distance(unitsB[indexNearest]->GetPosition());
		}
	}
	return *(unitsB[indexNearest]);
}

/*
	Return the farthest Units enemy from Unit's position
		--> point is the position of the Unit
		--> unitsB is the vector of Units to defeat
*/
Unit & AI::GetFarthestEnemy(const Point & point, std::vector<Unit*> & unitsB) const
{
	int indexFarthest = 0;
	float longestDistance = point.Distance(unitsB[indexFarthest]->GetPosition());

	unsigned int index;
	unsigned int size = unitsB.size();

	for (index = 1; index < size; ++index)
	{
		if (point.Distance((unitsB[index])->GetPosition()) > longestDistance)
		{
			indexFarthest = index;
			longestDistance = point.Distance(unitsB[indexFarthest]->GetPosition());
		}
	}
	return *(unitsB[indexFarthest]);
}

/*
	Return the enemy with the lowest value of a specific capacity
		--> indexCapacity is the index of the capacity to check (checking by using the overrided operator [] in see class Unit)
		--> unitsB is the vector of Units to defeat
*/
Unit & AI::GetLowestEnemy(unsigned int indexCapacity, std::vector<Unit*> & unitsB) const
{
	int indexLowest = 0;
	float lowestValue = unitsB[indexLowest]->operator[](indexCapacity).GetValue();

	unsigned int index;
	unsigned int size = unitsB.size();

	for (index = 1; index < size; ++index)
	{
		if (unitsB[index]->operator[](indexCapacity).GetValue() < lowestValue)
		{
			indexLowest = index;
			lowestValue = unitsB[indexLowest]->operator[](indexCapacity).GetValue();
		}
	}
	return *(unitsB[indexLowest]);
}

/*
	Return the enemy with the highest value of a specific capacity
		--> indexCapacity is the index of the capacity to check (checking by using the overrided operator [] in see class Unit)
		--> unitsB is the vector of Units to defeat
*/
Unit & AI::GetHighestEnemy(unsigned int indexCapacity, std::vector<Unit*> & unitsB) const
{
	int indexHighest = 0;
	float highestValue = unitsB[indexHighest]->operator[](indexCapacity).GetValue();

	unsigned int index;
	unsigned int size = unitsB.size();

	for (index = 1; index < size; ++index)
	{
		if (unitsB[index]->operator[](indexCapacity).GetValue() > highestValue)
		{
			indexHighest = index;
			highestValue = unitsB[indexHighest]->operator[](indexCapacity).GetValue();
		}
	}
	return *(unitsB[indexHighest]);
}

//Return a randomly generated Ai code for a unit
const std::string AI::GetRandomAiCode()
{
	int indexFirstChar = rand() % firstCharVector.size();
	int indexSecondChar = rand() % secondCharVector.size();

	return (firstCharVector[indexFirstChar] + secondCharVector[indexSecondChar]);
}