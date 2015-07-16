#pragma once

#include "Operator.h"
#include "Unit.h"
#include "Army.h"

class Smaller : public Operator
{
	public:
		Smaller() {};

		bool GetResult(std::shared_ptr<Extractor<float>> leftExtractor, std::shared_ptr<Extractor<float>> rightExtractor, Unit& u, Army& a, Army& o) const
		{
			return ( (leftExtractor->get(u, a, o)) > (rightExtractor->get(u, a, o)) );
		}
};

