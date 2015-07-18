#pragma once

#ifndef EXTRACTOR_VALUE_H
#define EXTRACTOR_VALUE_H

#include "Extractor.h"

//#include "ExtractorUnit.h"
//#include "ExtractorArmy.h"
//#include "ExtractorPoint.h"

class ExtractorValue : public Extractor<float>
{
	private:
		float _value;

	public:
		ExtractorValue(float value) : _value(value){};

		float get(Unit& u, Army& a, Army& o)
		{
			return _value;
		}
};

class ExtractorCxUnitValue : public Extractor<float>
{
	private:
		std::shared_ptr< Extractor<Unit> > _eUnit;
		int _indexCapacity;

	public:
		ExtractorCxUnitValue(std::shared_ptr< Extractor<Unit> > eUnit, int indexCapacity)
			: _eUnit(eUnit), _indexCapacity(indexCapacity){};

		float get(Unit& u, Army& a, Army& o)
		{
			return (_eUnit->get(u, a, o).getCapacity(_indexCapacity)->getValue());
		}
};

//Distance between a Unit position and a Point
class ExtractorDistanceUnitPointValue : public Extractor<float>
{
	private:
		std::shared_ptr< Extractor<Unit> > _eUnit;
		std::shared_ptr< Extractor<Point> >_ePoint;

	public:
		ExtractorDistanceUnitPointValue(std::shared_ptr< Extractor<Unit> > eUnit, std::shared_ptr< Extractor<Point> > ePoint)
			: _eUnit(eUnit), _ePoint(ePoint){};

		float get(Unit& u, Army& a, Army& o)
		{
			return (_ePoint->get(u, a, o).distance(_eUnit->get(u, a, o).getPosition()));
		}
};


// Max / Min / valeur moyenne de capacité d’un ensemble M / m / a 06 <set>
class ExtractorMaxCxArmyValue : public Extractor<float>
{
	private:
		std::shared_ptr< Extractor<Army> > _eArmy;
		int _indexCapacity;

	public:
		ExtractorMaxCxArmyValue(std::shared_ptr< Extractor<Army> > eArmy, int indexCapacity)
			: _eArmy(eArmy), _indexCapacity(indexCapacity){};

		float get(Unit& u, Army& a, Army& o)
		{
			return (_eArmy->get(u, a, o).getHighestUnit(_indexCapacity).getCapacity(_indexCapacity)->getValue());
		}
};

class ExtractorMinCxArmyValue : public Extractor<float>
{
	private:
		std::shared_ptr< Extractor<Army> > _eArmy;
		int _indexCapacity;

	public:
		ExtractorMinCxArmyValue(std::shared_ptr< Extractor<Army> > eArmy, int indexCapacity) 
			: _eArmy(eArmy), _indexCapacity(indexCapacity){};

		float get(Unit& u, Army& a, Army& o)
		{
			return (_eArmy->get(u, a, o).getLowestUnit(_indexCapacity).getCapacity(_indexCapacity)->getValue());
		}
};

class ExtractorAvgCxArmyValue : public Extractor<float>
{
	private:
		std::shared_ptr< Extractor<Army> > _eArmy;
		int _indexCapacity;

	public:
		ExtractorAvgCxArmyValue(std::shared_ptr< Extractor<Army> > eArmy, int indexCapacity) 
			: _eArmy(eArmy), _indexCapacity(indexCapacity){};

		float get(Unit& u, Army& a, Army& o)
		{
			return (_eArmy->get(u, a, o).getAverageCapacityValue(_indexCapacity));
		}
};



//distance minimale / maximale / moyenne d’un ensemble a un point M / m / a D <set> <point>
class ExtractorMaxDistancePointArmyValue : public Extractor<float>
{
	private:
		std::shared_ptr< Extractor<Army> > _eArmy;
		std::shared_ptr< Extractor<Point> >_ePoint;

	public:
		ExtractorMaxDistancePointArmyValue(std::shared_ptr< Extractor<Army> > eArmy, std::shared_ptr< Extractor<Point> > ePoint)
			: _eArmy(eArmy), _ePoint(ePoint){};

	float get(Unit& u, Army& a, Army& o)
	{
		Point p = _ePoint->get(u, a, o);

		return (_eArmy->get(u, a, o).getFurthestUnit(p).getPosition().distance(p));
	}
};

class ExtractorMinDistancePointArmyValue : public Extractor<float>
{
	private:
		std::shared_ptr< Extractor<Army> > _eArmy;
		std::shared_ptr< Extractor<Point> >_ePoint;

	public:
		ExtractorMinDistancePointArmyValue(std::shared_ptr< Extractor<Army> > eArmy, std::shared_ptr< Extractor<Point> > ePoint)
			: _eArmy(eArmy), _ePoint(ePoint){};

		float get(Unit& u, Army& a, Army& o)
		{
			Point p = _ePoint->get(u, a, o);

			return (_eArmy->get(u, a, o).getNearestUnit(p).getPosition().distance(p));
		}
};

class ExtractorAvgDistancePointArmyValue : public Extractor<float>
{
	private:
		std::shared_ptr< Extractor<Army> > _eArmy;
		std::shared_ptr< Extractor<Point> >_ePoint;

	public:
		ExtractorAvgDistancePointArmyValue(std::shared_ptr< Extractor<Army> > eArmy, std::shared_ptr< Extractor<Point> > ePoint)
			: _eArmy(eArmy), _ePoint(ePoint){};

		float get(Unit& u, Army& a, Army& o)
		{
			return (_eArmy->get(u, a, o).getAverageDistance(_ePoint->get(u, a, o)));
		}
};

#endif //EXTRACTOR_VALUE_H