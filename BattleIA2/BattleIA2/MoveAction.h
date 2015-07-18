#pragma once

#ifndef MOVE_ACTION_H
#define MOVE_ACTION_H

#include <iostream>

#include "Unit.h"
#include "Point.h"
#include "Action.h"

//Class representing the action to move a unit in direction of a specific position
class MoveAction : public Action
{
	private:
		Unit& _unit;
		Point _position;

	public:
		//Constructor taking in paramters the unit to move and the destination
		MoveAction(Unit& unit, const Point& position)
			: _unit(unit), _position(position) {}

		//Run the action
		//Log parameter indicate if we write something or not on the standard output
		void execute(bool log = false)
		{
			if (log)
				std::cout << "Unit " << _unit.getId() << " move from " << _unit.getPosition();
		
			_unit.moveToPosition(_position);

			if (log)
				std::cout << " to " << _unit.getPosition() << std::endl;
		}
};

#endif //MOVE_ACTION_H