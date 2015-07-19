#pragma once

#ifndef ACTION_H
#define ACTION_H

#include "Rectangle.h"

class Army;

//Interface representing action returned by AI
class Action
{
	public:
		//Run the action
		//Log parameter indicate if we write something or not on the standard output
		virtual void execute(Army& a, Army& o, const Rectangle& arena, bool log = false) = 0;
};

#endif //ACTION_H