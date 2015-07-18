#pragma once

#ifndef DECISION_NODE_H
#define DECISION_NODE_H

#include <sstream>

#include "Operator.h"
#include "Node.h"
#include "Extractor.h"

#include "Action.h"

#include "Unit.h"
#include "Army.h"

class DecisionNode : public Node
{
	private:
		std::unique_ptr<Extractor<float>> _leftExtractor;
		std::unique_ptr<Extractor<float>> _rightExtractor;

		std::unique_ptr<Operator> _operator;

		std::unique_ptr<Node> _leftNode;
		std::unique_ptr<Node> _rightNode;

	public:
		DecisionNode(std::stringstream& aiCode);

		std::unique_ptr<Action> get(Unit& u, Army& a, Army& o);
};

#endif //DECISION_NODE_H