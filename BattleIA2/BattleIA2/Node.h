#pragma once

#ifndef NODE_H
#define NODE_H

#include <memory>

class Unit;
class Army;

#include "Action.h"

class Node
{
	public:
		virtual std::unique_ptr<Action> get(Unit& u, Army& a, Army& o) = 0;
};

#endif //NODE_H