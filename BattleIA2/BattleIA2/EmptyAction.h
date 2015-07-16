#pragma once

#include <iostream>

#include "Unit.h"
#include "Action.h"
#include "Point.h"

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
		void execute(bool log = false)
		{
			if (log)
				std::cout << "Unit " << _unit->getId() << " do nothing..." << std::endl;
		}
};

