#include "OperatorFactory.h"

#include "Greater.h"
#include "Smaller.h"

std::unique_ptr<Operator> OperatorFactory::generateOperator(std::stringstream& aiCode)
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
				return std::unique_ptr<Operator>(new Smaller());
				//return nullptr;
			}
		}
	}
	catch (...)
	{
		std::cout << "Fin ou Erreur chaine code IA" << std::endl;
		return std::unique_ptr<Operator>(new Greater());
		//return nullptr;
	}
}