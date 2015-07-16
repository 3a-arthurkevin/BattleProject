#pragma once

#include <sstream>

#include "Unit.h"
#include "Army.h"

#include "ShotAction.h"
#include "MoveAction.h"
#include "EmptyAction.h"

class Node
{
	public:
		virtual std::unique_ptr<Action> get(Unit& u, Army& a, Army& o) = 0;
};

