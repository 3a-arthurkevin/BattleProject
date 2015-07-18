#pragma once

#ifndef OPERATOR_FACTORY_H
#define OPERATOR_FACTORY_H

#include <sstream>
#include "Operator.h"

class OperatorFactory
{
	public:
		static std::unique_ptr<Operator> generateOperator(std::stringstream& aiCode);
};

#endif //OPERATOR_FACTORY_H
