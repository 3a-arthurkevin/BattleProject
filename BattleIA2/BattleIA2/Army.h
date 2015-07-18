#pragma once

#ifndef ARMY_H
#define ARMY_H

#include <vector>

#include <memory>

#include <stdexcept>

#include <algorithm>
#include <numeric>
#include <limits>

#include <iostream>
#include <ostream>

#include "Unit.h"

//Class representing an army, i.e. a set of units
class Army
{
	private:
		//vector storing the units
		std::vector<std::shared_ptr<Unit> > _units;

		//Method for deep copying the units vector
		void copyUnits(const std::vector<std::shared_ptr<Unit> >& units);

		/*
			New private functions for Battle Round 2
		*/
		//sub part of the units vector filled with shared pointer Unit
		void copyUnits(const std::vector<std::shared_ptr<Unit> >& units, int nbElement);

	public:
		//Constructor with parameters the number of units, and the level of each
		Army(int size, int level);

		//Constructor from a vector of units, which will be deep copied
		Army(std::vector<std::shared_ptr<Unit> >& units);

		//Copy constructor
		Army(const Army& army);

		//Swap the content of the parameter and the current object
		void swap(Army& army);

		//Assignment operator overload
		Army& operator=(Army army);

		//Getter fot the units list
		std::vector<std::shared_ptr<Unit> >& getUnitsList()
		{
			return _units;
		}


		//Return the number of units
		int size()const
		{
			return _units.size();
		}

		//Return the unit with the given ID
		Unit& getUnit(int id)
		{
			auto it = std::find_if(_units.begin(), _units.end(), [id](const std::shared_ptr<Unit>& unit) {
				return unit->getId() == id;
			});
			if (it == _units.end())
				throw std::invalid_argument("wrong id : unit " + std::to_string(id) + " not found");
			
			return *(it->get());
		}


		//Get the unit the closest from the given position
		Unit& getNearestUnit(const Point& p);

		//Get the unit the furthest from the given position
		Unit& getFurthestUnit(const Point& p);


		//Get the unit with the lowest level for the given capacity
		Unit& getLowestUnit(int capa_index);


		//Get the unit with the highest level for the given capacity
		Unit& getHighestUnit(int capa_index);

		//Remove all the units with non positive life value
		void purge();

		//Provide a randomly mutated version of the current army
		Army mutate()const;

		//Star operator overloading, providing a random crossing of the current
		//army and the one provided in parameter.
		Army operator*(const Army& army)const;

		//Save the current army in the given output stream
		void save(std::ostream& out)const;

		//Load an army from the input stream
		static Army load(std::istream& in);


		/*
			New public functions for Battle Round 2
		*/

		//Return the average value of a capacity from the Units in the Army
		float getAverageCapacityValue(int indexCapacity);
		//Return the average value of the distance between a Point and all Units Position in the Army
		float getAverageDistance(Point point);

		//Return centroid of units position
		Point getCentroid();
		
		//Return an Army of N Units with the highest value of a capacity
		Army getNthHighestUnit(int nbElement, int indexCapacity);
		//Return an Army of N Units with the lowest value of a capacity
		Army getNthLowestUnit(int nbElement, int indexCapacity);
		
		//Return an Army of N Units the furthest from a Point
		Army getNthFurthestUnit(int nbElement, Point point);
		//Return an Army of N Units the nearest from a Point
		Army getNthNearestUnit(int nbElement, Point point);
		
		//Return an Army of Units who have a capacity greater than a threshold
		Army getSubArmyCapacityGreater(int indexCapacity, float threshold);
		//Return an Army of Units who have a capacity smaller than a threshold
		Army getSubArmyCapacitySmaller(int indexCapacity, float threshold);
		
};

//Shift operator overloading, printing the unit in the output stream.
inline std::ostream& operator<<(std::ostream& out, const Army& army)
{
	out << "====================ARMY====================================" << std::endl;
	std::vector<std::shared_ptr<Unit> >& units = const_cast<Army&>(army).getUnitsList();
	for (auto it = units.begin(); it != units.end(); ++it)
		out << (*it) << std::endl;
	out << "===================/ARMY====================================" << std::endl;

	return out;
};

#endif //ARMY_H