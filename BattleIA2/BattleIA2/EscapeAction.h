#pragma once

#include <iostream>

#include "Unit.h"
#include "Action.h"
#include "Point.h"

//Class representing the action to move a unit in direction of a specific position
class EscapeAction : public Action
{
private:
	Unit* _unit;
	Point _positionToAvoid;

public:
	//Constructor taking in paramters the unit to move and the destination
	EscapeAction(Unit& unit, const Point& position)
		: _unit(&unit), _positionToAvoid(position) {}

	//Run the action
	//Log parameter indicate if we write something or not on the standard output
	void execute(bool log = false)
	{
		if (log)
			std::cout << "Unit " << _unit->getId() << " escape from " << _unit->getPosition();

		_unit->escapeFromPosition(_positionToAvoid);

		if (log)
			std::cout << " to " << _unit->getPosition() << std::endl;
	}
};