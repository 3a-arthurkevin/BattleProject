#pragma once

#ifndef DECISION_NODE_H
#define DECISION_NODE_H

#include <sstream>

#include "Node.h"
#include "Extractor.h"

#include "Action.h"

#include "AiFactory.h"
#include "ExtractorFactory.h"
#include "OperatorFactory.h"


class DecisionNode : public Node
{
	private:
		std::shared_ptr<Extractor<float>> _leftExtractor;
		std::shared_ptr<Extractor<float>> _rightExtractor;

		std::unique_ptr<Operator> _operator;

		std::unique_ptr<Node> _leftNode;
		std::unique_ptr<Node> _rightNode;

	public:
		DecisionNode(std::stringstream& aiCode)
		{
			_leftExtractor = ExtractorFactory::getValueExtractor(aiCode);
			_operator = OperatorFactory::generateOperator(aiCode);
			_rightExtractor = ExtractorFactory::getValueExtractor(aiCode);

			_leftNode = AiFactory::generateNode(aiCode);
			_rightNode = AiFactory::generateNode(aiCode);
		}



		std::unique_ptr<Action> get(Unit& u, Army& a, Army& o)
		{
			if (_operator->GetResult(_leftExtractor, _rightExtractor, u, a, o))
				return _leftNode->get(u, a, o);
			return _rightNode->get(u, a, o);
		}
};

#endif //DECISION_NODE_H