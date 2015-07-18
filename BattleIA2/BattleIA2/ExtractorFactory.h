#pragma once

#ifndef EXTRACTOR_FACTORY_H
#define EXTRACTOR_FACTORY_H

#include <sstream>

#include "Extractor.h"

class ExtractorFactory
{
	public:
		static std::unique_ptr<Extractor<float>> getValueExtractor(std::stringstream& iaCode);
		static std::unique_ptr<Extractor<Unit>> getUnitExtractor(std::stringstream& iaCode);
		static std::unique_ptr<Extractor<Point>> getPointExtractor(std::stringstream& iaCode);
		static std::unique_ptr<Extractor<Army>> getArmyExtractor(std::stringstream& iaCode);
};

#endif //EXTRACTOR_FACTORY_H