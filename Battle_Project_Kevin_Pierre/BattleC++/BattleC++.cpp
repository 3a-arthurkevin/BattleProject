// BattleC++.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

#include <algorithm>

#include <iostream>

#include <time.h>

//#include "Capacity.h"
//#include "Armor.h"
//#include "Speed.h"
//#include "WeaponDamage.h"
//#include "WeaponRange.h"
//#include "LifePoint.h"
//#include "WeaponSpeed.h"

//#include "Unit.h"

//#include "Army.h"

//#include "Action.h"

#include "AI.h"

#include <fstream>

//Return the index of the unit who hasn't played yet
int GetPlayableUnitIndex(std::vector< Unit* > & units)
{
	int i;
	int nbUnitArmy = units.size();
	int randomLimit = nbUnitArmy * 2;
	int indexUnit;
	bool found = false;

	//Try to return a playabled unit randomly
	for (i = 0; i < randomLimit; ++i)
	{
		indexUnit = rand() % nbUnitArmy;
		if (!(units[indexUnit]->GetHasPlayed()) && units[indexUnit]->IsAlive())
			return indexUnit;
	}

	//If no playable unit found randomly, trying to return one iteratively
	if (!found)
	{
		for (i = 0; i < nbUnitArmy; ++i)
		{
			if (!(units[i]->GetHasPlayed()) && units[indexUnit]->IsAlive())
				return i;
		}
	}

	//Error case --> if no playable unit found in the entire army
	return -1;
}

void ApplyAction(Unit & unit, Action & unitAction, Army & armyB, std::string offenseArmy, std::string defenseArmy)
{
	if (unitAction.GetAction() == ActionType::Shoot)
	{
		unit.Shoot();
		armyB.GetUnit(unitAction.GetId()).TakeDamage(unit.GetWeaponDamage().GetValue());
		
		Unit unitAttacked = armyB.GetUnit(unitAction.GetId());
		//unitAttacked.TakeDamage(unit.GetWeaponDamage().GetValue());

		std::cout << "Unit " << unit.GetId() << "(" << offenseArmy << ") attacked Unit " << unitAttacked.GetId() << "(" << defenseArmy << ") has " << unitAttacked.GetLifePoint().GetValue() << " HP left" << std::endl;
	}
	else if (unitAction.GetAction() == ActionType::Move)
	{
		unit.SetPosition(unitAction.GetLocation());

		std::cout << "Unit " << unit.GetId() << "(" << offenseArmy << ") moved to " << unit.GetPosition() << std::endl;
	}
	else if (unitAction.GetAction() == ActionType::Flee)
	{
		unit.SetPosition(unitAction.GetLocation());

		std::cout << "Unit " << unit.GetId() << "(" << offenseArmy << ") fled to " << unit.GetPosition() << std::endl;
	}
	else
	{
		unit.SetPosition(unitAction.GetLocation());

		std::cout << "Unit " << unit.GetId() << "(" << offenseArmy << ") did nothing" << std::endl;
	}
}

Point GetRandomPosition(int nbUnit)
{
	Point p;
	float x = rand() % (nbUnit * 5);
	float y = rand() % (nbUnit * 5);

	p.SetX(x);
	p.SetY(y);

	return p;
}

void BattleLoop(Army & armyA, Army & armyB)
{
	unsigned int indexInit;
	unsigned int sizeInit = armyA.Size();

	for (indexInit = 0; indexInit < sizeInit; ++indexInit)
		armyA.GetUnitsList()[indexInit]->SetRandomPosition(GetRandomPosition(sizeInit));

	sizeInit = armyB.Size();

	for (indexInit = 0; indexInit < sizeInit; ++indexInit)
		armyB.GetUnitsList()[indexInit]->SetRandomPosition(GetRandomPosition(sizeInit));

	int i, indexUnit;
	bool armyATurn = true;
	bool found = false;
	int randomLimit = armyA.Size() * 2;

	AI aiBattle = AI();

	std::string offenseArmy;
	std::string defenseArmy;

	int turnNumber = 0;

	bool armyACanPlay = true;
	bool armyBCanPlay = true;

	while (armyA.Size() > 0 && armyB.Size() > 0)
	{
		std::cout << "============ Turn n" << ++turnNumber << " ============" << std::endl;

		std::vector<Unit*> unitsArmyA = armyA.GetUnitsList();
		std::vector<Unit*> unitsArmyB = armyB.GetUnitsList();

		int nbUnitArmyA = unitsArmyA.size();
		int nbUnitArmyB = unitsArmyB.size();
		int totalUnits = nbUnitArmyA + nbUnitArmyB;

		armyATurn = true;

		armyACanPlay = armyA.CanPlay();
		armyBCanPlay = armyB.CanPlay();

		while (armyACanPlay || armyBCanPlay)
		{
			//ArmyA turn
			if (armyATurn == true)
			{
				offenseArmy = "Army A";
				defenseArmy = "Army B";

				indexUnit = GetPlayableUnitIndex(unitsArmyA);

				if (indexUnit >= 0)
				{
					Action unitAction = aiBattle(*(unitsArmyA[indexUnit]), armyA, armyB);

					ApplyAction(*(unitsArmyA[indexUnit]), unitAction, armyB, offenseArmy, defenseArmy);

					armyB.Purge();
				}
				else
				{
					//std::cout << "Error - unitIndex < 0 --> no unit can move" << std::endl;
				}
			}
			//ArmyB turn
			else
			{
				offenseArmy = "Army B";
				defenseArmy = "Army A";

				indexUnit = GetPlayableUnitIndex(unitsArmyB);

				if (indexUnit >= 0)
				{
					Action unitAction = aiBattle(*(unitsArmyB[indexUnit]), armyB, armyA);

					ApplyAction(*(unitsArmyB[indexUnit]), unitAction, armyA, offenseArmy, defenseArmy);

					armyA.Purge();
				}
				else
				{
					//std::cout << "Error - unitIndex < 0 --> no unit can move" << std::endl;
				}
			}

			nbUnitArmyA = unitsArmyA.size();
			nbUnitArmyB = unitsArmyB.size();

			if (nbUnitArmyA == 0 || nbUnitArmyB == 0)
				break;

			armyACanPlay = armyA.CanPlay();
			armyBCanPlay = armyB.CanPlay();

			armyATurn = !armyATurn;
		}

		armyA.Refresh();
		armyB.Refresh();

		std::cout << std::endl;
		std::cout << std::endl;

		/*
		for (int i = 0; i < armyA.Size(); ++i)
		{
			//armyA.GetUnitsList()[i]->SetRandomPosition(GetRandomPosition(armyA.Size()));

			std::cout << "Id : " << armyA.GetUnitsList()[i]->GetId() << std::endl;

			//std::cout << armyA.GetUnitsList()[i]->GetAiCode() << std::endl;

			std::cout << armyA.GetUnitsList()[i]->GetPosition() << std::endl;

			//std::cout << "Speep : " << armyA.GetUnitsList()[i]->operator[](0).GetValue() << std::endl;
			std::cout << "Life : " << armyA.GetUnitsList()[i]->operator[](1).GetValue() << "/" << armyA.GetUnitsList()[i]->GetLifePoint().GetMaxValue() << std::endl;
			std::cout << "Armor : " << armyA.GetUnitsList()[i]->operator[](2).GetValue() << std::endl;
			//std::cout << "Regen : " << armyA.GetUnitsList()[i]->operator[](3).GetValue() << std::endl;
			std::cout << "W-Damage : " << armyA.GetUnitsList()[i]->operator[](4).GetValue() << std::endl;
			//std::cout << "W-Range : " << armyA.GetUnitsList()[i]->operator[](5).GetValue() << std::endl;
			std::cout << "W-Speed : " << armyA.GetUnitsList()[i]->operator[](6).GetValue() << "/" << armyA.GetUnitsList()[i]->GetWeaponSpeed().GetMaxValue() << std::endl;

			std::cout << std::endl;
		}

		std::cout << " ------- " << std::endl;
		std::cout << std::endl;

		for (int i = 0; i < armyB.Size(); ++i)
		{
			//armyB.GetUnitsList()[i]->SetRandomPosition(GetRandomPosition(armyB.Size()));

			std::cout << "Id : " << armyB.GetUnitsList()[i]->GetId() << std::endl;

			//std::cout << armyB.GetUnitsList()[i]->GetAiCode() << std::endl;

			std::cout << armyB.GetUnitsList()[i]->GetPosition() << std::endl;

			//std::cout << "Speep : " << armyB.GetUnitsList()[i]->operator[](0).GetValue() << std::endl;
			std::cout << "Life : " << armyB.GetUnitsList()[i]->operator[](1).GetValue() << "/" << armyB.GetUnitsList()[i]->GetLifePoint().GetMaxValue() << std::endl;
			std::cout << "Armor : " << armyB.GetUnitsList()[i]->operator[](2).GetValue() << std::endl;
			//std::cout << "Regen : " << armyB.GetUnitsList()[i]->operator[](3).GetValue() << std::endl;
			std::cout << "W-Damage : " << armyB.GetUnitsList()[i]->operator[](4).GetValue() << std::endl;
			//std::cout << "W-Range : " << armyB.GetUnitsList()[i]->operator[](5).GetValue() << std::endl;
			std::cout << "W-Speed : " << armyB.GetUnitsList()[i]->operator[](6).GetValue() << "/" << armyB.GetUnitsList()[i]->GetWeaponSpeed().GetMaxValue() << std::endl;

			std::cout << std::endl;
		}
		*/
	}

	std::cout << "Army A score : " << armyA.Size() << std::endl;
	std::cout << "Army B score : " << armyB.Size() << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	//Initialisation du random pour que ca ne fasse pas la même chose à chaque Run (à ne faire qu'un fois dans le code)
	srand((unsigned int)time(NULL));

	
	int I, T, N, X, Y;
	std::cout << "Iteration : ";
	std::cin >> I; // --> nb Iteration

	std::cout << "Score criteria : ";
	std::cin >> T; // --> army criteria
	
	std::cout << "Nb army : ";
	std::cin >> N; // --> nb Army
	
	std::cout << "Nb Unit : ";
	std::cin >> X; // --> nb Unit
	
	std::cout << "Global level : ";
	std::cin >> Y; // --> global level


	if (T >= ((N - 1) * X))
		T = ((N - 1) * X) / 2;

	std::vector<Army> armiesVector;

	
	int i, j, k, l;

	//Creating N armies, with X units who are level Y
	for (i = 0; i < N; ++i)
		armiesVector.push_back(Army(X, Y));

	int nbArmies = armiesVector.size();

	int nbArmyBest = 0.1f * nbArmies;
	int nbArmyCrossing = 0.3f * nbArmies;
	int nbArmyMutating = 0.3 * nbArmies;
	int nbLeftOver = nbArmies - (nbArmyBest + nbArmyCrossing + nbArmyMutating);

	int indexRandom = 0;

	std::vector<Army> newGeneration;

	bool loopBreak = false;

	for (i = 0; i < I; ++i)
	{
		for (j = 0; j < (nbArmies-1); ++j)
		{
			for (k = j + 1; k < nbArmies; ++k)
			{
				Army armyA(armiesVector[j].GetUnitsList());
				Army armyB(armiesVector[k].GetUnitsList());

				BattleLoop(armyA, armyB);

				armiesVector[j].AddScore(armyA.Size());
				armiesVector[k].AddScore(armyB.Size());
			}
			
			std::sort(armiesVector.rbegin(), armiesVector.rend());
			
			if (armiesVector[0].GetScore() < T)
			{
				newGeneration.clear();

				for (l = 0; l < nbArmyBest; ++l);
				{
					newGeneration.push_back(armiesVector[l]);
				}
				for (l = 0; l < nbArmyCrossing; ++l);
				{
					indexRandom = rand() % nbArmies;
					newGeneration.push_back( (armiesVector[l] * armiesVector[indexRandom]) );
				}
				for (l = 0; l < nbArmyMutating; ++l);
				{
					armiesVector[l].Mutate();
					newGeneration.push_back(armiesVector[l]);
				}
				for (l = 0; l < nbLeftOver; ++l);
				{
					newGeneration.push_back(Army(X, Y));
				}

				armiesVector.clear();

				armiesVector = newGeneration;
			}
			else
			{
				loopBreak = true;
				break;
			}
		}

		if (loopBreak)
			break;
	}
	
	std::cout << "Score best army : " << armiesVector[0].GetScore() << std::endl;

	std::string const fileName = "C:/army_" + std::to_string(X) + "_" + std::to_string(Y) + ".save";

	std::string const file(fileName);
	std::ofstream flux(fileName.c_str());

	std::vector<Unit*> units = armiesVector[0].GetUnitsList();

	if (flux)
	{
		int i;
		int size = units.size();

		for (i = 0; i < size; ++i)
		{
			flux << units[i]->operator[](0).GetLevel() << " " << units[i]->operator[](1).GetLevel() << " " << units[i]->operator[](2).GetLevel() << " " << units[i]->operator[](3).GetLevel() << " " << units[i]->operator[](4).GetLevel() << " " << units[i]->operator[](5).GetLevel() << " " << units[i]->operator[](6).GetLevel() << std::endl;
		}
	}
	else
	{
		std::cout << "Error - Can't write in file." << std::endl;
	}

	//Permet de maintenir la console lors d'un Run (sinon elle se ferme toute seul -__-')
	int endSimu = 0;
	std::cout << "End of the simulation" << std::endl;
	std::cout << "Write any character from your keybord then press Enter to end the simulation : ";
	std::cin >> endSimu;
	std::cin.get();

	return 0;
}
