#pragma once

#ifndef ACTION_NODE_H
#define ACTION_NODE_H

#include "Unit.h"
#include"Army.h"
#include "Point.h"

#include "Extractor.h"

#include "Action.h"

class ShotActionNode : public Node
{	
	private:
		std::shared_ptr<Extractor<Unit&>> _unitTargetExtractor;

	public:
		ShotActionNode(std::stringstream& aiCode);

		std::unique_ptr<Action> get(Unit& u, Army& a, Army& o);
};

class MoveActionNode : public Node
{
	private:
		std::shared_ptr<Extractor<Point>> _destinationExtractor;

	public:
		MoveActionNode(std::stringstream& aiCode);

		std::unique_ptr<Action> get(Unit& u, Army& a, Army& o);
};

class EscapeActionNode : public Node
{
	private:
		std::shared_ptr<Extractor<Point>> _destinationExtractor;

	public:
		EscapeActionNode(std::stringstream& aiCode);

		std::unique_ptr<Action> get(Unit& u, Army& a, Army& o);
};

class EmptyActionNode : public Node
{
	public:
		EmptyActionNode() {}

		std::unique_ptr<Action> get(Unit& u, Army& a, Army& o);
};

#endif //ACTION_NODE_H