#pragma once

#ifndef GREATER_H
#define GREATER_H

#include "Operator.h"
#include "Extractor.h"

#include "Unit.h"
#include "Army.h"

class Greater : public Operator
{
	public:
		Greater() {};

		bool GetResult(std::unique_ptr<Extractor<float>>& leftExtractor, std::unique_ptr<Extractor<float>>& rightExtractor, Unit& u, Army& a, Army& o) const
		{
			return ( (leftExtractor->get(u, a, o)) > (rightExtractor->get(u, a, o)) );
		}
};

#endif //GREATER_H