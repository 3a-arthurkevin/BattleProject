#pragma once

#ifndef EXTRACTOR_POINT_H
#define EXTRACTOR_POINT_H

#include "Extractor.h"


class ExtractorPointUnitPoint : public Extractor<Point>
{
	private:
		std::unique_ptr< Extractor<Unit&> > _eUnit;

	public:
		ExtractorPointUnitPoint(std::unique_ptr< Extractor<Unit&> >& eUnit)
		{
			_eUnit = std::move(eUnit);
		};

		Point get(Unit& u, Army& a, Army& o)
		{
			return (_eUnit->get(u, a, o).getPosition());
		}
};

class ExtractorCentroidArmyPoint : public Extractor<Point>
{
	private:
		std::unique_ptr< Extractor<SetUnit> > _eArmy;

	public:
		ExtractorCentroidArmyPoint(std::unique_ptr< Extractor<SetUnit> >& eArmy)
		{
			_eArmy = std::move(eArmy);
		};

		Point get(Unit& u, Army& a, Army& o)
		{
			return (_eArmy->get(u, a, o).getCentroid());
		}
};

#endif //EXTRACTOR_POINT_H