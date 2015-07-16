#pragma once

#include <sstream>

#include "Extractor.h"
#include "ExtractorValue.h"
#include "ExtractorUnit.h"
#include "ExtractorArmy.h"
#include "ExtractorPoint.h"


class ExtractorFactory
{
	public:
		static std::shared_ptr<Extractor<float>> getValueExtractor(std::stringstream& iaCode);
		static std::shared_ptr<Extractor<Unit>> getUnitExtractor(std::stringstream& iaCode);
		static std::shared_ptr<Extractor<Point>> getPointExtractor(std::stringstream& iaCode);
		static std::shared_ptr<Extractor<Army>> getArmyExtractor(std::stringstream& iaCode);
};

