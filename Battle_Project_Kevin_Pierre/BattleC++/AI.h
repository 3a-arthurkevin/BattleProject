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

		//Foncteur déterminant l'action d'un unité appartenant à l'armée A, contre l'armée B
		const Action operator()(Unit & unit, Army & armyA, Army & armyB) const;
		
		bool EnemyInRange(const float range, const Point & point, Army & armyB) const;
		
		void GetEnemiesInRange(std::vector< Unit* > & enemiesInRange, const float range, const Point & point, Army & armyB) const;
		
		Unit & GetNearestInRange(float range, const Point & point, const std::vector< Unit* > & enemiesInRange) const;
		Unit & GetFarthestInRange(float range, const Point & point, const std::vector< Unit* > & enemiesInRange) const;
		
		Unit & GetLowestInRange(unsigned int indexCapacity, std::vector< Unit* > enemiesInRange) const;
		Unit & GetHighestInRange(unsigned int indexCapacity, std::vector< Unit* > enemiesInRange) const;
		
		static const std::string GetRandomIaCode();
};

#endif