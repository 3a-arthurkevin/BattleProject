#pragma once

#ifndef EXTRACTOR_ARMY_H
#define EXTRACTOR_ARMY_H

#include "Extractor.h"

//#include "ExtractorUnit.h"
//#include "ExtractorArmy.h"
//#include "ExtractorPoint.h"

class ExtractorArmyA : public Extractor<Army>
{
	public:
		Army get(Unit& u, Army& a, Army& o)
		{
			return a;
		}
};

class ExtractorArmyO : public Extractor<Army>
{
	public:
		Army get(Unit& u, Army& a, Army& o)
		{
			return o;
		}
};

//N ayant la plus grande / petite capacité au sein d’un ensemble : N L06 <set> ou  N H06 <set>
class ExtractorNMaxCxSetArmy : public Extractor<Army>
{
	private:
		int _nbElement;
		int _indexCapacity; 
		std::shared_ptr< Extractor<Army> > _eArmy;

	public:
		ExtractorNMaxCxSetArmy(int nbElement, int indexCapacity, std::shared_ptr< Extractor<Army> > eArmy)
			: _nbElement(nbElement), _indexCapacity(indexCapacity), _eArmy(eArmy) {};

		Army get(Unit& u, Army& a, Army& o)
		{
			return (_eArmy->get(u, a, o).getNthHighestUnit(_nbElement, _indexCapacity));
		}
};

class ExtractorNMinCxSetArmy : public Extractor<Army>
{
	private:
		int _nbElement;
		int _indexCapacity;
		std::shared_ptr< Extractor<Army> > _eArmy;

	public:
		ExtractorNMinCxSetArmy(int nbElement, int indexCapacity, std::shared_ptr< Extractor<Army> > eArmy)
			: _nbElement(nbElement), _indexCapacity(indexCapacity), _eArmy(eArmy) {};

		Army get(Unit& u, Army& a, Army& o)
		{
			return (_eArmy->get(u, a, o).getNthLowestUnit(_nbElement, _indexCapacity));
		}
};

//N plus proches / loin d’un point au sein d’un ensemble : N LD <point> <set> ou N HD <point> <set>
class ExtractorNMaxDistancePointSetArmy : public Extractor<Army>
{
	private:
		int _nbElement;
		std::shared_ptr< Extractor<Point> > _ePoint;
		std::shared_ptr< Extractor<Army> > _eArmy;

	public:
		ExtractorNMaxDistancePointSetArmy(int nbElement, std::shared_ptr< Extractor<Point> > ePoint, std::shared_ptr< Extractor<Army> > eArmy)
			: _nbElement(nbElement), _ePoint(ePoint), _eArmy(eArmy) {};

		Army get(Unit& u, Army& a, Army& o)
		{
			return (_eArmy->get(u, a, o).getNthFurthestUnit(_nbElement, _ePoint->get(u, a, o)));
		}
};

class ExtractorNMinDistancePointSetArmy : public Extractor<Army>
{
	private:
		int _nbElement;
		std::shared_ptr< Extractor<Point> > _ePoint;
		std::shared_ptr< Extractor<Army> > _eArmy;

	public:
		ExtractorNMinDistancePointSetArmy(int nbElement, std::shared_ptr< Extractor<Point> > ePoint, std::shared_ptr< Extractor<Army> > eArmy)
			: _nbElement(nbElement), _ePoint(ePoint), _eArmy(eArmy) {};

		Army get(Unit& u, Army& a, Army& o)
		{
			return (_eArmy->get(u, a, o).getNthNearestUnit(_nbElement, _ePoint->get(u, a, o)));
		}
};

//sous ensemble ayant capacité / distance > / < seuil : T L06 [val] <set> ou T H06 [val] <set>
class ExtractorTCxGreaterValueSetArmy : public Extractor<Army>
{
	private:
		int _indexCapacity;
		std::shared_ptr< Extractor<float> > _eValue;
		std::shared_ptr< Extractor<Army> > _eArmy;

	public:
		ExtractorTCxGreaterValueSetArmy(int indexCapacity, std::shared_ptr< Extractor<float> > eValue, std::shared_ptr< Extractor<Army> > eArmy)
			: _indexCapacity(_indexCapacity), _eValue(eValue), _eArmy(eArmy) {};

		Army get(Unit& u, Army& a, Army& o)
		{
			return (_eArmy->get(u, a, o).getSubArmyCapacityGreater(_indexCapacity, _eValue->get(u, a, o)));
		}
};

class ExtractorTCxSmallerValueSetArmy : public Extractor<Army>
{
	private:
		int _indexCapacity;
		std::shared_ptr< Extractor<float> > _eValue;
		std::shared_ptr< Extractor<Army> > _eArmy;

	public:
		ExtractorTCxSmallerValueSetArmy(int indexCapacity, std::shared_ptr< Extractor<float> > eValue, std::shared_ptr< Extractor<Army> > eArmy)
			: _indexCapacity(_indexCapacity), _eValue(eValue), _eArmy(eArmy) {};

		Army get(Unit& u, Army& a, Army& o)
		{
			return (_eArmy->get(u, a, o).getSubArmyCapacitySmaller(_indexCapacity, _eValue->get(u, a, o)));
		}
};

#endif //EXTRACTOR_POINT_H