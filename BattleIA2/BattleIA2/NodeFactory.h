#pragma once

#ifndef AI_FACTORY_H
#define AI_FACTORY_H

#include <sstream>

#include "Node.h"

class NodeFactory
{
	public:
		static std::unique_ptr<Node> generateNode(std::stringstream& aiCode);
};

#endif //AI_FACTORY_H