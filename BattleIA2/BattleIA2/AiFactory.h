#pragma once

#include <sstream>

#include "Node.h"

#include "Operator.h"
#include "Greater.h"
#include "Smaller.h"

class AiFactory
{
	public:
		static std::unique_ptr<Node> generateNode(std::stringstream& aiCode);
		static std::unique_ptr<Operator> generateOperator(std::stringstream& aiCode);
};