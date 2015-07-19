#pragma once

#ifndef SHOT_ACTION_H
#define SHOT_ACTION_H

#include <iomanip>
#include <iostream>

#include "Unit.h"
#include "Action.h"

//Class representing the action of attacking one unit with another
class ShotAction : public Action
{
	private:
		Unit* _unit;
		Unit* _opponent;

	public:
		//Constructor with as first paramter the unit attacking, and as second, its target
		ShotAction(Unit& unit, Unit& opponent)
			: _unit(&unit), _opponent(&opponent) {}

		//Run the action
		//Log parameter indicate if we write something or not on the standard output
		void execute(Army& a, Army& o, const Rectangle& arena, bool log = false)
		{
			// Test if _target is in range of _unit
			// If _target not in range, unit go closer to _target
				// Test if futur positionToMove is inside the arena

			Point posUnit = _unit->getPosition();
			Point posTarget = _opponent->getPosition();
			float range = _unit->getRange().getValue();

			float distanceBetweenUnits = posUnit.distance(posTarget);

			//Test target in range
			if (distanceBetweenUnits <= range)
			{
				_opponent->takeDamage(_unit->getDamage().getValue());

				_unit->shoot();
				if (log)
				{
					std::cout << "Unit " << _unit->getId() << " shoot Unit " << _opponent->getId();
					float hp = _opponent->getLife().getValue();

					if (hp > 0)
						std::cout << " (" << hp << "hp remaining)" << std::endl;
					else
						std::cout << " (dead !)" << std::endl;
				}
			}
			//Move closer to target
			else
			{
				Point posToMove;

				float k = (_unit->getSpeed().getValue() / distanceBetweenUnits);
				Point directionalVector(posTarget - posUnit);
				Point futurLocation = Point(posUnit + (directionalVector * k));
				
				//check if not inside arena
				if (!(arena.include(futurLocation)))
					posToMove = futurLocation; //posUnit;
				else
					posToMove = futurLocation;

				_unit->moveToPosition(posToMove);

				if (log)
				{
					std::cout << "Unit " << _unit->getId() << " move from " << _unit->getPosition();
					std::cout << " to " << _unit->getPosition() << " in order to attack" << std::endl;
				}
			}
		}
};

#endif //SHOT_ACTION_H