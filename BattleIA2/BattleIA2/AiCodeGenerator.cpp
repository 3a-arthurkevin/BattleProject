#include "AiCodeGenerator.h"

//Generate an AiCode for a unit
std::string AiCodeGenerator::generateAiCode()
{
	std::string aiCode;
	aiCode.clear();

	int endCondition = 0;

	aiCode = generateDecisionNodeCode(endCondition);
	
	return aiCode;
}

//Generate an ActionNode AiCode
std::string AiCodeGenerator::generateActionNodeCode()
{
	std::string pieceOfAiCode;
	pieceOfAiCode.clear();

	pieceOfAiCode += '!';

	int randomValue = rand() % 2 + 1;

	//Case ShotAction
	if (randomValue == 1)
		pieceOfAiCode += ('A' + generateExtractorUnitCode());
	//Case EscapeAction
	else if (randomValue == 2)
		pieceOfAiCode += ('E' + generateExtractorPointCode());
	//Case EmptyAction
	else
		pieceOfAiCode += 'N';

	return pieceOfAiCode;
}

//Generate a DecisionNode AiCode (recursive)
std::string AiCodeGenerator::generateDecisionNodeCode(int& endCondition)
{
	std::string aiCode;
	aiCode.clear();

	aiCode += '?';
	//Creating left extractor , operator, right extractor
	aiCode += (generateExtractorValueCode() + generateOperatorCode() + generateExtractorValueCode());

	int randomValue = 0;

	//Creation node left and node right
	// 80% of ActionNode
	// 20% of DecisionNode
	while (endCondition < 2)
	{
		randomValue = rand() % 10 + 1;

		if (randomValue >= 1 && randomValue <= 8)
		{
			++endCondition;
			aiCode += generateActionNodeCode();
		}
		else
		{
			--endCondition;
			aiCode += generateDecisionNodeCode(endCondition);
		}
	}

	return aiCode;
}

//Generate an Extractor<float> AiCode
std::string AiCodeGenerator::generateExtractorValueCode()
{
	std::string extractorValueCode;
	extractorValueCode.clear();

	int randomValue = rand() % 5 + 1;

	//Case [val]
	if(randomValue == 1)
	{
		std::string strValue = ('[' + std::to_string(static_cast<float>(rand() % 11)) + ']');
		extractorValueCode += strValue;
	}
	//Case C0-C6<Unit>
	else if (randomValue == 2)
	{
		std::string indexCapacity = std::to_string(rand() % 7);
		extractorValueCode += ('C' + indexCapacity + generateExtractorUnitCode());
	}
	//Case D<Unit><Point>
	else if (randomValue == 3)
	{
		extractorValueCode += ('D' + generateExtractorUnitCode() + generateExtractorPointCode());
	}
	//Case M/m/a0-6<Set>
	else if(randomValue == 4)
	{
		int random = rand() % 3 + 1;
		std::string indexCapacity = std::to_string(rand() % 7);

		if (random == 1)
		{
			extractorValueCode += ('M' + indexCapacity + generateExtractorArmyCode());
		}
		else if (random == 2)
		{
			extractorValueCode += ('m' + indexCapacity + generateExtractorArmyCode());
		}
		else
		{
			extractorValueCode += ('a' + indexCapacity + generateExtractorArmyCode());
		}
	}
	//Case M/m/aD<Set><Point>
	else
	{
		int random = rand() % 3 + 1;

		if (random == 1)
		{
			extractorValueCode += ("MD" + generateExtractorArmyCode() + generateExtractorPointCode());
		}
		else if (random == 2)
		{
			extractorValueCode += ("mD" + generateExtractorArmyCode() + generateExtractorPointCode());
		}
		else
		{
			extractorValueCode += ("aD" + generateExtractorArmyCode() + generateExtractorPointCode());
		}
	}

	return extractorValueCode;
}

//Generate an Extractor<Unit> AiCode
std::string AiCodeGenerator::generateExtractorUnitCode()
{
	std::string extractorUnitCode;
	extractorUnitCode.clear();

	int randomValue = rand() % 3 + 1;

	//Case U
	if (randomValue == 1)
	{
		extractorUnitCode += 'U';
	}
	//Case L0-6<Set> | H0-6<Set>
	else if (randomValue == 2)
	{
		int random = rand() % 2 + 1;
		std::string indexCapacity = std::to_string(rand() % 7);

		if (random == 1)
		{
			extractorUnitCode += ('L' + indexCapacity + generateExtractorArmyCode());
		}
		else
		{
			extractorUnitCode += ('H' + indexCapacity + generateExtractorArmyCode());
		}
	}
	//Case LD<Set><Point> | HD<Set><Point>
	else
	{
		int random = rand() % 2 + 1;

		if (random == 1)
		{
			extractorUnitCode += ("LD" + generateExtractorArmyCode() + generateExtractorPointCode());
		}
		else
		{
			extractorUnitCode += ("HD" + generateExtractorArmyCode() + generateExtractorPointCode());
		}
	}

	return extractorUnitCode;
}

//Generate an Extractor<Point> AiCode
std::string AiCodeGenerator::generateExtractorPointCode()
{
	std::string extractorPointCode;
	extractorPointCode.clear();

	int randomValue = rand() % 2 + 1;

	//Case B<Set>
	if (randomValue == 1)
	{
		extractorPointCode += ('B' + generateExtractorArmyCode());
	}
	//Case P<Unit>
	else
	{
		extractorPointCode += ('P' + generateExtractorUnitCode());
	}

	return extractorPointCode;
}

//Generate an Extractor<Army> AiCode
std::string AiCodeGenerator::generateExtractorArmyCode()
{
	std::string extractorArmyCode;
	extractorArmyCode.clear();

	int randomValue = rand() % 4 + 1;

	//Case A
	if (randomValue == 1)
	{
		extractorArmyCode += 'A';
	}
	//Case O
	else if(randomValue == 2)
	{
		extractorArmyCode += 'O';
	}
	//Case TL0-6[val]<Set> | TH0-6[val]<Set>
	else if (randomValue == 3)
	{
		int random = rand() % 2 + 1;
		std::string indexCapacity = std::to_string(rand() % 7);
		std::string strValue = ('[' + std::to_string(static_cast<float>(rand() % 11)) + ']');

		if (random == 1)
		{
			extractorArmyCode += ("TL" + indexCapacity  + strValue + generateExtractorArmyCode());
		}
		else
		{
			extractorArmyCode += ("TH" + indexCapacity +  strValue +  generateExtractorArmyCode());
		}
	}
	//Case NL0-6<Set> | NH0-6<Set>
	//Case NLD<Point><Set> |  NLD<Point><Set>
	else
	{
		randomValue = rand() % 2 + 1;
		//Case NL0-6<Set> | NH0-6<Set>
		if (randomValue == 1)
		{
			int random = rand() % 2 + 1;
			std::string nbElement = std::to_string(rand() % 9 + 1);
			std::string indexCapacity = std::to_string(rand() % 7);

			if (random == 1)
			{
				extractorArmyCode += (nbElement + 'L' + indexCapacity + generateExtractorArmyCode());
			}
			else
			{
				extractorArmyCode += (nbElement + 'H' + indexCapacity + generateExtractorArmyCode());
			}
		}
		//Case NLD<Point><Set> |  NLD<Point><Set>
		else
		{
			int random = rand() % 2 + 1;
			std::string nbElement = std::to_string(rand() % 9 + 1);

			if (random == 1)
			{
				extractorArmyCode += (nbElement + "LD" + generateExtractorPointCode() + generateExtractorArmyCode());
			}
			else
			{
				extractorArmyCode += (nbElement + "HD" + generateExtractorPointCode() + generateExtractorArmyCode());
			}
		}
	}

	return extractorArmyCode;
}

//Generate an Operator AiCode
std::string AiCodeGenerator::generateOperatorCode()
{
	std::string operatorCode;
	operatorCode.clear();

	int randomValue = rand() % 2 + 1;

	//Case Greater Operator
	if (randomValue == 1)
		operatorCode += '>';
	//Case Smaller Operator
	else
		operatorCode += '<';

	return operatorCode;
}