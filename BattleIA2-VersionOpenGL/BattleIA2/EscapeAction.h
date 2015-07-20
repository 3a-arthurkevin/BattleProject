#pragma once

#ifndef ESCAPE_ACTION_H
#define ESCAPE_ACTION_H

#include <iostream>

#include "Unit.h"
#include "Army.h"
#include "Point.h"
#include "Action.h"

//Class representing the action to move a unit in direction of a specific position
class EscapeAction : public Action
{
private:
	Unit* _unit;
	Point _positionToAvoid;

public:
	//Constructor taking in paramters the unit to move and the destination
	EscapeAction(Unit& unit, const Point positionToAvoid)
		: _unit(&unit), _positionToAvoid(positionToAvoid) {}

	//Run the action
	//Log parameter indicate if we write something or not on the standard output
	void execute(bool log = false)
	{
		if (log)std::cout << "Unit " << _unit->getId() << " do nothing..." << std::endl;

	}
};

#endif //ESCAPE_ACTION_H