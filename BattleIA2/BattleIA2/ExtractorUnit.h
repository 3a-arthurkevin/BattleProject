#pragma once

#ifndef EXTRACTOR_UNIT_H
#define EXTRACTOR_UNIT_H

#include "Extractor.h"

//#include "ExtractorUnit.h"
//#include "ExtractorArmy.h"
//#include "ExtractorPoint.h"

class ExtractorUnit : public Extractor<Unit>
{
	public:
		Unit get(Unit& u, Army& a, Army& o)
		{
			return u;
		}
};

//unité qui a la valeur min / max de capacité au sein d’un ensemble (L0L6 ou H0H6) <set>

class ExtractorMaxCxArmyUnit : public Extractor<Unit>
{
	private:
		std::shared_ptr< Extractor<Army> >_eArmy;
		int _indexCapacity;

	public:
		ExtractorMaxCxArmyUnit(std::shared_ptr< Extractor<Army> > eArmy, int indexCapacity)
			: _eArmy(eArmy), _indexCapacity(indexCapacity){};

		Unit get(Unit& u, Army& a, Army& o)
		{
			return (_eArmy->get(u, a, o).getHighestUnit(_indexCapacity));
		}
};

class ExtractorMinCxArmyUnit : public Extractor<Unit>
{
	private:
		std::shared_ptr< Extractor<Army> >_eArmy;
		int _indexCapacity;

	public:
		ExtractorMinCxArmyUnit(std::shared_ptr< Extractor<Army> > eArmy, int indexCapacity)
			: _eArmy(eArmy), _indexCapacity(indexCapacity){};

		Unit get(Unit& u, Army& a, Army& o)
		{
			return (_eArmy->get(u, a, o).getLowestUnit(_indexCapacity));
		}
};

//unité la plus proche / loin d’un point au sein d’un ensemble (LD ou HD) <set> <point>
class ExtractorMaxDistancePointArmyUnit : public Extractor<Unit>
{
	private:
		std::shared_ptr< Extractor<Army> > _eArmy;
		std::shared_ptr< Extractor<Point> >_ePoint;

	public:
		ExtractorMaxDistancePointArmyUnit(std::shared_ptr< Extractor<Army> > eArmy, std::shared_ptr< Extractor<Point> > ePoint)
			: _eArmy(eArmy), _ePoint(ePoint){};

		Unit get(Unit& u, Army& a, Army& o)
		{
			Point p = _ePoint->get(u, a, o);

			return (_eArmy->get(u, a, o).getFurthestUnit(p));
		}
};

class ExtractorMinDistancePointArmyUnit : public Extractor<Unit>
{
	private:
		std::shared_ptr< Extractor<Army> > _eArmy;
		std::shared_ptr< Extractor<Point> >_ePoint;

	public:
		ExtractorMinDistancePointArmyUnit(std::shared_ptr< Extractor<Army> > eArmy, std::shared_ptr< Extractor<Point> > ePoint)
			: _eArmy(eArmy), _ePoint(ePoint){};

		Unit get(Unit& u, Army& a, Army& o)
		{
			Point p = _ePoint->get(u, a, o);

			return (_eArmy->get(u, a, o).getNearestUnit(p));
		}
};

#endif //EXTRACTOR_UNIT_H