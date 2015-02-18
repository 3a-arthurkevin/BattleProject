#include "AI.h"

AI::~AI(void)
{
}

AI::AI(void)
{
	
}

const Action AI::operator()(Unit & unit, Army & armyA, Army & armyB) const
{
	
	Action actionToDo;
	
	std::string firstChar(1, unit.GetAiCode()[0]);
	std::string secondChar(1, unit.GetAiCode()[1]);
	unsigned int secondCharInt = std::atoi(&(unit.GetAiCode()[1]));

	//Check is unit can shoot
	if (unit.CanShoot())
	{
		//Check if at least one enemy is at shooting range
		if (this->EnemyInRange(unit.GetWeaponRange().GetValue(), unit.GetPosition(), armyB))
		{
			actionToDo.SetAction(ActionType::Shoot);

			std::vector< Unit* > enemiesInRange;
			this->GetEnemiesInRange(enemiesInRange, unit.GetWeaponRange().GetValue(), unit.GetPosition(), armyB);

			//Applying action according to unit's ai code
			if (firstChar.compare("L") == 0)
			{

				if (secondChar.compare("D"))
				{
					Unit enemyToShoot = this->GetNearestInRange(unit.GetWeaponRange().GetValue(), unit.GetPosition(), enemiesInRange);
					actionToDo.SetId(enemyToShoot.GetId());
					actionToDo.SetLocation(enemyToShoot.GetPosition());
				}
				else if (secondCharInt >= 0 && secondCharInt <= 6)
				{
					Unit enemyToShoot = this->GetLowestInRange(secondCharInt, enemiesInRange);
					actionToDo.SetId(enemyToShoot.GetId());
					actionToDo.SetLocation(enemyToShoot.GetPosition());
				}
				else
					std::cout << "Error - 2nd char of ai code unknown" << std::endl;
				
			}
			else if (firstChar.compare("H") == 0)
			{
				if (secondChar.compare("D"))
				{
					Unit enemyToShoot = this->GetFarthestInRange(unit.GetWeaponRange().GetValue(), unit.GetPosition(), enemiesInRange);
					actionToDo.SetId(enemyToShoot.GetId());
					actionToDo.SetLocation(enemyToShoot.GetPosition());
				}
				else if (secondCharInt >= 0 && secondCharInt <= 6)
				{
					Unit enemyToShoot = this->GetHighestInRange(secondCharInt, enemiesInRange);
				}
				else
					std::cout << "Error - 2nd char of ai code unknown" << std::endl;
			}
			else
				std::cout << "Error - 1st char of ai code unknown" << std::endl;
		}
		//S'apporcher
		else
		{
			actionToDo.SetAction(ActionType::Move);

			std::vector< Unit* > enemiesInRange;
			this->GetEnemiesInRange(enemiesInRange, unit.GetSpeed().GetValue(), unit.GetPosition(), armyB);
			Unit nearestEnemy = this->GetNearestInRange(unit.GetSpeed().GetValue(), unit.GetPosition(), enemiesInRange);
			actionToDo.SetLocation(nearestEnemy.GetPosition());
		}
	}
	//Sinon fuite
	else
	{
		actionToDo.SetAction(ActionType::Flee);

		std::vector< Unit* > enemiesInRange;
		this->GetEnemiesInRange(enemiesInRange, unit.GetSpeed().GetValue(), unit.GetPosition(), armyB);
		Unit nearestEnemy = *(armyB.GetFarthestUnit(unit.GetPosition()));
		actionToDo.SetLocation(nearestEnemy.GetPosition());

		float k = (unit.GetSpeed().GetValue() / unit.GetPosition().Distance(nearestEnemy.GetPosition()));
		
		Point pA(unit.GetPosition());
		Point pB(nearestEnemy.GetPosition());
		Point directionalVector = (pB - pA);

		actionToDo.SetLocation(directionalVector * -k);
	}
	
	return actionToDo;
}

bool AI::EnemyInRange(const float range, const Point & point, Army & armyB) const
{
	Circle circlularRange(point, range);

	unsigned int indexArmyB;
	unsigned int sizeArmyB = armyB.Size();

	for (indexArmyB = 0; indexArmyB < sizeArmyB; ++indexArmyB)
	{
		if (circlularRange.Include( (armyB.GetUnitsList()[indexArmyB])->GetPosition()))
			return true;
	}
	return false;
}

void AI::GetEnemiesInRange(std::vector< Unit* > & enemiesInRange, float range, const Point & point, Army & armyB) const
{
	Circle circlularRange(point, range);

	unsigned int indexArmyB;
	unsigned int sizeArmyB = armyB.Size();

	for (indexArmyB = 0; indexArmyB < sizeArmyB; ++indexArmyB)
	{
		if (circlularRange.Include((*armyB.GetUnitsList()[indexArmyB]).GetPosition()))
			enemiesInRange.push_back(armyB.GetUnitsList()[indexArmyB]);
	}
}

Unit & AI::GetNearestInRange(float range, const Point & point, const std::vector< Unit* > & enemiesInRange) const
{
	Unit * nearestUnit = enemiesInRange[0];
	float shortestDistance = point.Distance(nearestUnit->GetPosition());

	unsigned int index;
	unsigned int size = enemiesInRange.size();

	for (index = 1; index < size; ++index)
	{
		if (point.Distance((enemiesInRange[index])->GetPosition()) < shortestDistance)
		{
			nearestUnit = enemiesInRange[index];
			shortestDistance = point.Distance(nearestUnit->GetPosition());
		}
	}
	return *nearestUnit;
}

Unit & AI::GetFarthestInRange(const float range, const Point & point, const std::vector< Unit* > & enemiesInRange) const
{
	Unit * farthestUnit = enemiesInRange[0];
	
	float longestDistance = point.Distance(farthestUnit->GetPosition());

	unsigned int index;
	unsigned int size = enemiesInRange.size();

	for (index = 1; index < size; ++index)
	{
		if (point.Distance((enemiesInRange[index])->GetPosition()) > longestDistance)
		{
			farthestUnit = enemiesInRange[index];
			longestDistance = point.Distance(farthestUnit->GetPosition());
		}
	}
	return *farthestUnit;
}

Unit & AI::GetLowestInRange(unsigned int indexCapacity, std::vector< Unit* > enemiesInRange) const
{
	Unit * lowestUnit = enemiesInRange[0];
	float lowestValue = (*lowestUnit)[indexCapacity].GetValue();

	unsigned int index;
	unsigned int size = enemiesInRange.size();

	for (index = 1; index < size; ++index)
	{
		if ((*(enemiesInRange[index]))[indexCapacity].GetValue() < lowestValue)
		{
			lowestUnit = enemiesInRange[index];
			lowestValue = (*lowestUnit)[indexCapacity].GetValue();
		}
	}
	return *lowestUnit;
}

Unit & AI::GetHighestInRange(unsigned int indexCapacity, std::vector< Unit* > enemiesInRange) const
{
	Unit * highestUnit = enemiesInRange[0];
	float highestValue = (*highestUnit)[indexCapacity].GetValue();

	unsigned int index;
	unsigned int size = enemiesInRange.size();

	for (index = 1; index < size; ++index)
	{
		if ((*(enemiesInRange[index]))[indexCapacity].GetValue() > highestValue)
		{
			highestUnit = enemiesInRange[index];
			highestValue = (*highestUnit)[indexCapacity].GetValue();
		}
	}
	return *highestUnit;
}

const std::string AI::GetRandomIaCode()
{
	int indexFirstChar = rand() % firstCharVector.size();
	int indexSecondChar = rand() % secondCharVector.size();

	return (firstCharVector[indexFirstChar] + secondCharVector[indexSecondChar]);
}