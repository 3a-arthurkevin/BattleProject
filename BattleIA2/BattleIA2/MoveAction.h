#pragma once

#ifndef MOVE_ACTION_H
#define MOVE_ACTION_H

#include <iostream>

#include "Unit.h"
#include "Army.h"
#include "Point.h"
#include "Action.h"

//Class representing the action to move a unit in direction of a specific position
class MoveAction : public Action
{
	private:
		Unit* _unit;
		Point _positionToMove;

	public:
		//Constructor taking in paramters the unit to move and the destination
		MoveAction(Unit& unit, const Point positionToMove)
			: _unit(&unit), _positionToMove(positionToMove) {}

		//Run the action
		//Log parameter indicate if we write something or not on the standard output
		void execute(Army& a, Army& o, const Rectangle& arena, bool log = false)
		{
			if (log)
				std::cout << "Unit " << _unit->getId() << " move from " << _unit->getPosition();
		
			// Test if positionToMove is reachable with unit speed 
			//		And 
			// Test if futur positionToMove is inside the arena

			Point posUnit = _unit->getPosition();
			float distanceBetweenUnits = posUnit.distance(_positionToMove);

			if (distanceBetweenUnits > 1.f || distanceBetweenUnits < -1.f)
			{
				float k = (_unit->getSpeed().getValue() / distanceBetweenUnits);
				Point directionalVector(_positionToMove - posUnit);
				Point futurLocation = Point(posUnit + (directionalVector * k));

				if (!(arena.include(futurLocation)))
					_positionToMove = posUnit;
			}
			else
				_positionToMove = posUnit;


			_unit->moveToPosition(_positionToMove);

			if (log)
				std::cout << " to " << _unit->getPosition() << std::endl;
		}
};

#endif //MOVE_ACTION_H