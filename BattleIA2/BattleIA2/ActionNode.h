#pragma once

#ifndef ACTION_NODE_H
#define ACTION_NODE_H

#include "Unit.h"
#include"Army.h"
#include "Point.h"

#include "ExtractorFactory.h"
#include "Extractor.h"

#include "Action.h"
#include "ShotAction.h"
#include "MoveAction.h"
#include "EscapeAction.h"
#include "EmptyAction.h"

class ShotActionNode : public Node
{	
	private:
		std::shared_ptr<Extractor<Unit>> _unitTargetExtractor;

	public:
		ShotActionNode(std::stringstream& aiCode)
		{
			_unitTargetExtractor = ExtractorFactory::getUnitExtractor(aiCode);
		}

		std::unique_ptr<Action> get(Unit& u, Army& a, Army& o)
		{
			return std::unique_ptr<Action>( new ShotAction(u, _unitTargetExtractor->get(u, a, o)) );
		}
};

class MoveActionNode : public Node
{
	private:
		std::shared_ptr<Extractor<Point>> _destinationExtractor;

	public:
		MoveActionNode(std::stringstream& aiCode)
		{
			_destinationExtractor = ExtractorFactory::getPointExtractor(aiCode);
		}

		std::unique_ptr<Action> get(Unit& u, Army& a, Army& o)
		{
			return std::unique_ptr<Action>(new MoveAction(u, _destinationExtractor->get(u, a, o)));
		}
};

class EscapeActionNode : public Node
{
	private:
		std::shared_ptr<Extractor<Point>> _destinationExtractor;

	public:
		EscapeActionNode(std::stringstream& aiCode)
		{
			_destinationExtractor = ExtractorFactory::getPointExtractor(aiCode);
		}

		std::unique_ptr<Action> get(Unit& u, Army& a, Army& o)
		{
			return std::unique_ptr<Action>(new EscapeAction(u, _destinationExtractor->get(u, a, o)));
		}
};

class EmptyActionNode : public Node
{
	public:
		EmptyActionNode() {}

		std::unique_ptr<Action> get(Unit& u, Army& a, Army& o)
		{
			return std::unique_ptr<EmptyAction>(new EmptyAction(u));
		}
};

#endif //ACTION_NODE_H