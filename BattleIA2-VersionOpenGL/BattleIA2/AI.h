#pragma once

#ifndef AI_H
#define AI_H


#include <iostream>
#include <memory>

#include "Action.h"
#include "MoveAction.h"
#include "ShotAction.h"
#include "EmptyAction.h"

#include "Unit.h"
#include "Army.h"
#include "Rectangle.h"


//class representing an Artificial Intelligence
class AI
{
	public:
		//Parenthesis overloading for applying the AI on the unit provided in parameter
		//Return the action which have to be done by the unit in this context
		std::unique_ptr<Action> operator()(Unit& unit, Army& allies, Army& opponents, const Rectangle& arena);
};

#endif //AI_H
