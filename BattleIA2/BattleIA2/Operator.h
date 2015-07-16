#pragma once

#include "Extractor.h"

class Operator
{
	public:
		virtual bool GetResult(std::shared_ptr<Extractor<float>> leftExtractor, std::shared_ptr<Extractor<float>> rightExtractor, Unit& u, Army& a, Army& o) const = 0;
};

