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

		//Copy constructor (copy shared pointer)
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

		//Get the unit the closest from the given position
		Unit& getNearestUnit(const Point& p);
		//Get the unit the furthest from the given position
		Unit& getFurthestUnit(const Point& p);
		
		//Get the unit with the lowest level for the given capacity
		Unit& getLowestUnit(int capa_index);
		//Get the unit with the highest level for the given capacity
		Unit& getHighestUnit(int capa_index);

		//Get Average capacity value on a specific capacity of an army ( or subArmy)
		float getAverageCapacityValue(int indexCapacity);
		//Get average distance of an army from a point
		float getAverageDistance(Point point);

		//Return the centroid of an army (or SubArmy)
		Point getCentroid();

		//Get N unit having the highest Value of a specific capacity
		SetUnit getNthHighestUnit(int nbElement, int indexCapacity);
		//Get N unit having the lowest Value of a specific capacity
		SetUnit getNthLowestUnit(int nbElement, int indexCapacity);

		//Get N unit who are the farest from a Point
		SetUnit getNthFurthestUnit(int nbElement, Point point);
		//Get N unit who are the nearest from a Point
		SetUnit getNthNearestUnit(int nbElement, Point point);

		//Get a subArmy having a specific capacity value greater than a threshold
		SetUnit getSubArmyCapacityGreater(int indexCapacity, float threshold);
		//Get a subArmy having a specific capacity value smaller than a threshold
		SetUnit getSubArmyCapacitySmaller(int indexCapacity, float threshold);
};

#endif
