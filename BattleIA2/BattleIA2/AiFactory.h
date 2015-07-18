#pragma once

#ifndef AI_FACTORY_H
#define AI_FACTORY_H

#include <sstream>

#include "Node.h"
#include "Operator.h"

class AiFactory
{
	public:
		static std::unique_ptr<Node> generateNode(std::stringstream& aiCode);
};

#endif //AI_FACTORY_H