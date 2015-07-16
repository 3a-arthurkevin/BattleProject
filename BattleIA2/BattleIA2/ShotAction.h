#pragma once

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
		void execute(bool log = false)
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
};

