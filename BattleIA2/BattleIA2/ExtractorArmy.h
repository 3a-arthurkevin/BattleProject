#pragma once

#ifndef EXTRACTOR_ARMY_H
#define EXTRACTOR_ARMY_H

#include "Extractor.h"

#include "SetUnit.h"

class ExtractorArmyA : public Extractor<SetUnit>
{
	public:
		SetUnit get(Unit& u, Army& a, Army& o)
		{
			return SetUnit(a.getUnitsList());
		}
};

class ExtractorArmyO : public Extractor< SetUnit >
{
	public:
		SetUnit get(Unit& u, Army& a, Army& o)
		{
			return SetUnit(o.getUnitsList());
		}
};

//N ayant la plus grande / petite capacité au sein d’un ensemble : N L06 <set> ou  N H06 <set>
class ExtractorNMaxCxSetArmy : public Extractor< SetUnit >
{
	private:
		int _nbElement;
		int _indexCapacity; 
		std::unique_ptr< Extractor< SetUnit > > _eArmy;

	public:
		ExtractorNMaxCxSetArmy(int nbElement, int indexCapacity, std::unique_ptr< Extractor< SetUnit > >& eArmy)
			: _nbElement(nbElement), _indexCapacity(indexCapacity) 
		{
			_eArmy = std::move(eArmy);
		};

		SetUnit get(Unit& u, Army& a, Army& o)
		{
			return (_eArmy->get(u, a, o).getNthHighestUnit(_nbElement, _indexCapacity));
		}
};

class ExtractorNMinCxSetArmy : public Extractor< SetUnit >
{
	private:
		int _nbElement;
		int _indexCapacity;
		std::unique_ptr< Extractor< SetUnit > > _eArmy;

	public:
		ExtractorNMinCxSetArmy(int nbElement, int indexCapacity, std::unique_ptr< Extractor< SetUnit > >& eArmy)
			: _nbElement(nbElement), _indexCapacity(indexCapacity)
		{
			_eArmy = std::move(eArmy);
		};

		SetUnit get(Unit& u, Army& a, Army& o)
		{
			return (_eArmy->get(u, a, o).getNthLowestUnit(_nbElement, _indexCapacity));
		}
};

//N plus proches / loin d’un point au sein d’un ensemble : N LD <point> <set> ou N HD <point> <set>
class ExtractorNMaxDistancePointSetArmy : public Extractor< SetUnit >
{
	private:
		int _nbElement;
		std::unique_ptr< Extractor<Point> > _ePoint;
		std::unique_ptr< Extractor< SetUnit > > _eArmy;

	public:
		ExtractorNMaxDistancePointSetArmy(int nbElement, std::unique_ptr< Extractor<Point> >& ePoint, std::unique_ptr< Extractor< SetUnit > >& eArmy)
			: _nbElement(nbElement)
		{
			_ePoint = std::move(ePoint);
			_eArmy = std::move(eArmy);
		};

		SetUnit get(Unit& u, Army& a, Army& o)
		{
			return (_eArmy->get(u, a, o).getNthFurthestUnit(_nbElement, _ePoint->get(u, a, o)));
		}
};

class ExtractorNMinDistancePointSetArmy : public Extractor< SetUnit >
{
	private:
		int _nbElement;
		std::unique_ptr< Extractor<Point> > _ePoint;
		std::unique_ptr< Extractor< SetUnit > > _eArmy;

	public:
		ExtractorNMinDistancePointSetArmy(int nbElement, std::unique_ptr< Extractor<Point> >& ePoint, std::unique_ptr< Extractor< SetUnit > >& eArmy)
			: _nbElement(nbElement)
		{
			_ePoint = std::move(ePoint);
			_eArmy = std::move(eArmy);
		};

		SetUnit get(Unit& u, Army& a, Army& o)
		{
			return (_eArmy->get(u, a, o).getNthNearestUnit(_nbElement, _ePoint->get(u, a, o)));
		}
};

//sous ensemble ayant capacité / distance > / < seuil : T L06 [val] <set> ou T H06 [val] <set>
class ExtractorTCxGreaterValueSetArmy : public Extractor< SetUnit >
{
	private:
		int _indexCapacity;
		std::unique_ptr< Extractor<float> > _eValue;
		std::unique_ptr< Extractor< SetUnit > > _eArmy;

	public:
		ExtractorTCxGreaterValueSetArmy(int indexCapacity, std::unique_ptr< Extractor<float> >& eValue, std::unique_ptr< Extractor< SetUnit > >& eArmy)
			: _indexCapacity(_indexCapacity)
		{
			_eValue = std::move(eValue);
			_eArmy = std::move(eArmy);
		};

		SetUnit get(Unit& u, Army& a, Army& o)
		{
			return (_eArmy->get(u, a, o).getSubArmyCapacityGreater(_indexCapacity, _eValue->get(u, a, o)));
		}
};

class ExtractorTCxSmallerValueSetArmy : public Extractor< SetUnit >
{
	private:
		int _indexCapacity;
		std::unique_ptr< Extractor<float> > _eValue;
		std::unique_ptr< Extractor< SetUnit > > _eArmy;

	public:
		ExtractorTCxSmallerValueSetArmy(int indexCapacity, std::unique_ptr< Extractor<float> >& eValue, std::unique_ptr< Extractor< SetUnit > >& eArmy)
			: _indexCapacity(_indexCapacity)
		{
			_eValue = std::move(eValue);
			_eArmy = std::move(eArmy);
		};

		SetUnit get(Unit& u, Army& a, Army& o)
		{
			return (_eArmy->get(u, a, o).getSubArmyCapacitySmaller(_indexCapacity, _eValue->get(u, a, o)));
		}
};

#endif //EXTRACTOR_POINT_H