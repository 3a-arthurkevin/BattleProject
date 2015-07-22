#pragma once

#ifndef SET_UNIT_H
#define SET_UNIT_H

#include "Unit.h"
#include "Army.h"

class SetUnit
{
	private:
		std::vector< std::shared_ptr<Unit> > _setUnit;

	public:
		SetUnit();

		SetUnit(const SetUnit& setUnit);
		SetUnit(std::vector< std::shared_ptr<Unit> > unitVector);

		std::vector< std::shared_ptr<Unit> > getSetUnit()
		{
			return _setUnit;
		}

		void setSetUnit(std::vector< std::shared_ptr<Unit> > setUnit)
		{
			_setUnit = setUnit;
		}

		SetUnit copySetUnit();
		SetUnit copySubSetUnit(const std::vector<std::shared_ptr<Unit> >& units, int nbElement);
		void copySetUnit(const std::vector<std::shared_ptr<Unit> >& units);

		void swap(SetUnit& setUnit);

		SetUnit& operator=(SetUnit army);

		Unit& getNearestUnit(const Point& p);
		Unit& getFurthestUnit(const Point& p);

		Unit& getLowestUnit(int capa_index);
		Unit& getHighestUnit(int capa_index);

		float getAverageCapacityValue(int indexCapacity);
		float getAverageDistance(Point point);

		Point getCentroid();

		SetUnit getNthHighestUnit(int nbElement, int indexCapacity);
		SetUnit getNthLowestUnit(int nbElement, int indexCapacity);

		SetUnit getNthFurthestUnit(int nbElement, Point point);
		SetUnit getNthNearestUnit(int nbElement, Point point);

		SetUnit getSubArmyCapacityGreater(int indexCapacity, float threshold);
		SetUnit getSubArmyCapacitySmaller(int indexCapacity, float threshold);
};

#endif
