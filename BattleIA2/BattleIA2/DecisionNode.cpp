#include "DecisionNode.h"

#include "NodeFactory.h"
#include "ExtractorFactory.h"
#include "OperatorFactory.h"

#include "EmptyAction.h"

DecisionNode::DecisionNode(std::stringstream& aiCode)
{
	_leftExtractor = ExtractorFactory::getValueExtractor(aiCode);
	_operator = OperatorFactory::generateOperator(aiCode);
	_rightExtractor = ExtractorFactory::getValueExtractor(aiCode);

	_leftNode = NodeFactory::generateNode(aiCode);
	_rightNode = NodeFactory::generateNode(aiCode);
}


std::unique_ptr<Action> DecisionNode::get(Unit& u, Army& a, Army& o)
{
	try
	{
		if (_operator->GetResult(_leftExtractor, _rightExtractor, u, a, o))
			return _leftNode->get(u, a, o);
		return _rightNode->get(u, a, o);
	}
	catch (...)
	{
		std::cout << "Error - Decision Node - Get" << std::endl;
		return std::unique_ptr<Action>(new EmptyAction(u));
	}
}