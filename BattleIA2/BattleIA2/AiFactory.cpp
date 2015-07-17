#include "AiFactory.h"

#include "ActionNode.h"
//Probleme d'include car DecisionNode include lui meme AiFactory (cycle)
#include "DecisionNode.h"

std::unique_ptr<Node> AiFactory::generateNode(std::stringstream& aiCode)
{
	aiCode.exceptions(std::stringstream::eofbit | std::stringstream::failbit | std::stringstream::badbit);
	try
	{
		char c;
		aiCode >> c;

		switch (c)
		{
			//Case ActionNode
			case '!':
			{
				aiCode << c;

				switch (c)
				{
				case 'A':
					return std::unique_ptr<Node>(new ShotActionNode(aiCode));
				/*
				case 'M':
					return std::unique_ptr<Node>(new MoveActionNode(aiCode));
				*/
				case 'E':
					return std::unique_ptr<Node>(new EscapeActionNode(aiCode));

				case 'N':
					return std::unique_ptr<Node>(new EmptyActionNode());

				default:
					return std::unique_ptr<Node>(new EmptyActionNode());
				}
			}

			//Case DecisionNode
			case '?':
			{
				return std::unique_ptr<Node>(new DecisionNode(aiCode));
			}

			//Default case (Error in the AiCode)
			default:
			{
				return std::unique_ptr<Node>(new EmptyActionNode());
			}
		}
	}
	catch (...)
	{
		std::cout << "Fin ou Erreur chaine code IA" << std::endl;
		return std::unique_ptr<Node>(new EmptyActionNode());
	}
}

std::unique_ptr<Operator> AiFactory::generateOperator(std::stringstream& aiCode)
{
	aiCode.exceptions(std::stringstream::eofbit | std::stringstream::failbit | std::stringstream::badbit);
	try
	{
		char c;
		aiCode >> c;

		switch (c)
		{
			//Case Greater
			case '>':
			{
				return std::unique_ptr<Operator>(new Greater());
			}
			
				//Case Smaller
			case '<':
			{
				return std::unique_ptr<Operator>(new Smaller());
			}
			
				//Default case (Error in the AiCode)
			default:
			{
				return nullptr;
			}
		}
	}
	catch (...)
	{
		std::cout << "Fin ou Erreur chaine code IA" << std::endl;
		return nullptr;
	}
}
