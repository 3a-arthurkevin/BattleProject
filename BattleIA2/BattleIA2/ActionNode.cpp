#include "ActionNode.h"

#include "ShotAction.h"
#include "MoveAction.h"
#include "EscapeAction.h"
#include "EmptyAction.h"

#include "ExtractorFactory.h"

ShotActionNode::ShotActionNode(std::stringstream& aiCode)
{
	_unitTargetExtractor = ExtractorFactory::getUnitExtractor(aiCode);
}

std::unique_ptr<Action> ShotActionNode::get(Unit& u, Army& a, Army& o)
{
	try
	{
		return std::unique_ptr<Action>(new ShotAction(u, _unitTargetExtractor->get(u, a, o)));
	}
	catch (...)
	{
		//std::cout << "Error - Shoot Action Node - Get" << std::endl;
		return std::unique_ptr<Action>(new EmptyAction(u));
	}
}

//---------------------------------------


MoveActionNode::MoveActionNode(std::stringstream& aiCode)
{
	_destinationExtractor = ExtractorFactory::getPointExtractor(aiCode);
}

std::unique_ptr<Action> MoveActionNode::get(Unit& u, Army& a, Army& o)
{
	try
	{
		return std::unique_ptr<Action>(new MoveAction(u, _destinationExtractor->get(u, a, o)));
	}
	catch (...)
	{
		//std::cout << "Error - Move Action Node - Get" << std::endl;
		return std::unique_ptr<Action>(new EmptyAction(u));
	}
}

//---------------------------------------


EscapeActionNode::EscapeActionNode(std::stringstream& aiCode)
{
	_destinationExtractor = ExtractorFactory::getPointExtractor(aiCode);
}

std::unique_ptr<Action> EscapeActionNode::get(Unit& u, Army& a, Army& o)
{
	try
	{
		return std::unique_ptr<Action>(new EscapeAction(u, _destinationExtractor->get(u, a, o)));
	}
	catch (...)
	{
		//std::cout << "Error - Escape Action Node - Get" << std::endl;
		return std::unique_ptr<Action>(new EmptyAction(u));
	}
}

//---------------------------------------


std::unique_ptr<Action> EmptyActionNode::get(Unit& u, Army& a, Army& o)
{
	return std::unique_ptr<EmptyAction>(new EmptyAction(u));
}
