#include "AI.h"


//Parenthesis overloading for applying the AI on the unit provided in parameter
//Return the action which have to be done by the unit in this context
std::unique_ptr<Action> AI::operator()(Unit& unit, Army& allies, Army& opponents, const Rectangle& arena)
{
	try
	{
		//Check if unit can shoot --> getting the target
		if (unit.getFirerate().canShoot())
		{
			std::string code = unit.getIACode();
			Unit* target;
			
			//Case when the Unit has to shoot the farest or the nearest enemy
			if (code[1] == 'D')
			{
				if (code[0] == 'L')
					target = &(opponents.getNearestUnit(unit.getPosition()));
				else 
					target = &(opponents.getFurthestUnit(unit.getPosition()));
			}
			//Case when the Unit has to shoot an enemy according to the highest or the lowest value of a capacity
			else
			{
				if (code[0] == 'L')
					target = &(opponents.getLowestUnit(int(code[1] - '0')));
				else
					target = &(opponents.getHighestUnit(int(code[1] - '0')));
			}

			if (target != nullptr)
			{
				//Check if the target is hitable
				//Case when the enemy is out of range
				if (target->getPosition().distance(unit.getPosition()) > unit.getRange().getValue())
					return std::unique_ptr<Action>(new MoveAction(unit, target->getPosition()));
				//Case when the enemy is in range
				else
					return std::unique_ptr<Action>(new ShotAction(unit, *target));
			}
			else
				return std::unique_ptr<Action>(new EmptyAction(unit));
		}
		//Case when unit can't shoot --> getting closer to the neasest enemy
		else
		{
			/*
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

				Point futurLocation = Point(unit.GetPosition() + (directionalVector * k));

				if (arena.include(futurLocation))
					actionToDo.SetLocation(futurLocation);
				else
					actionToDo.SetAction(ActionType::None);
				*/
			Unit& target = opponents.getNearestUnit(unit.getPosition());
			Point p = (2 * unit.getPosition()) - target.getPosition();
			return std::unique_ptr<Action>(new MoveAction(unit, 1000 * p));
		}
	}
	catch (/*std::invalid_argument& e*/ ...)
	{
		//std::cout<<e.what()<<std::endl;
		return std::unique_ptr<Action>(new EmptyAction(unit));
	}
}

