#pragma once

#ifndef EMPTY_ACTION_H
#define EMPTY_ACTION_H

#include <iostream>

#include "Unit.h"
#include "Army.h"
#include "Action.h"
#include "Rectangle.h"

//Class representing an action which do nothing
class EmptyAction : public Action
{
	private:
		Unit* _unit;

	public:
		//Constructor
		EmptyAction(Unit& unit) :_unit(&unit) {}

		//Run the action
		//Log parameter indicate if we write something or not on the standard output
		void execute(Army& a, Army& o, const Rectangle& arena, bool log = false)
		{
			if (log)
				std::cout << "Unit " << _unit->getId() << " do nothing..." << std::endl;
		}
};

#endif //EMPTY_ACTION_H

