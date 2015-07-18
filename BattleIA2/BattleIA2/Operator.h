#pragma once

#ifndef OPERATOR_H
#define OPERATOR_H

#include "Extractor.h"

#include "Unit.h"
#include "Army.h"

class Operator
{
	public:
		virtual bool GetResult(std::shared_ptr<Extractor<float>> leftExtractor, std::shared_ptr<Extractor<float>> rightExtractor, Unit& u, Army& a, Army& o) const = 0;
};

#endif //OPERATOR_H