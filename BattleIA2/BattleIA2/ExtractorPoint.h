#pragma once

#ifndef EXTRACTOR_POINT_H
#define EXTRACTOR_POINT_H

#include "Extractor.h"

//#include "ExtractorUnit.h"
//#include "ExtractorArmy.h"
//#include "ExtractorPoint.h"

class ExtractorPointUnitPoint : public Extractor<Point>
{
	private:
		std::shared_ptr< Extractor<Unit> > _eUnit;

	public:
		ExtractorPointUnitPoint(std::shared_ptr< Extractor<Unit> > eUnit)
			: _eUnit(_eUnit) {};

		Point get(Unit& u, Army& a, Army& o)
		{
			return (_eUnit->get(u, a, o).getPosition());
		}
};

class ExtractorCentroidArmyPoint : public Extractor<Point>
{
	private:
		std::shared_ptr< Extractor<Army> > _eArmy;

	public:
		ExtractorCentroidArmyPoint(std::shared_ptr< Extractor<Army> > eArmy)
			: _eArmy(eArmy) {};

		Point get(Unit& u, Army& a, Army& o)
		{
			return (_eArmy->get(u, a, o).getCentroid());
		}
};

#endif //EXTRACTOR_POINT_H