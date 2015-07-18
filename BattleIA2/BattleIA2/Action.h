#pragma once

#ifndef ACTION_H
#define ACTION_H

#include "Army.h"

//Interface representing action returned by AI
class Action
{
	public:
		//Run the action
		//Log parameter indicate if we write something or not on the standard output
		virtual void execute(bool log = false) = 0;
};

#endif //ACTION_H