#pragma once

#ifndef AI_CODE_GENERATOR_H
#define AI_CODE_GENERATOR_H

#include <iostream>
#include <string> 

class AiCodeGenerator
{
	private:
		static std::string generateActionNodeCode();
		static std::string generateDecisionNodeCode(int& endCondition);

		static std::string generateExtractorValueCode();
		static std::string generateExtractorUnitCode();
		static std::string generateExtractorPointCode();
		static std::string generateExtractorArmyCode();

		static std::string generateOperatorCode();

	public:
		static std::string generateAiCode();
};

#endif //AI_CODE_GENERATOR_H


