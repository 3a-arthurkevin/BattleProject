#ifndef ARMY_H
#define ARMY_H

#include <vector>
#include <iostream>

#include "Unit.h"

class Army
{
	/*
		Unit* pour le projet du 2nd semestre --> car héritage de la classe army
	*/

	private:
		std::vector< Unit * > _units;

	public:
		~Army(void);

		Army(int nbUnit, int globalLevel);
		Army(std::vector< Unit * > & units);

		std::vector< Unit * > & GetUnitsList();

		Unit * GetUnit(unsigned int id);

		const int Size() const;

		Unit * GetNearestUnit(const Point & point) const;
		Unit * GetFarthestUnit(const Point & point) const;
		Unit * GetLowestUnit(int indexCapacity) const;
		Unit * GetHighestUnit(int indexCapacity) const;

		void Purge();

		bool operator < (const Army & army) const;
		bool operator > (const Army & army) const;
		bool operator >= (const Army & army) const;
		bool operator <= (const Army & army)const;

		bool operator == (const Army & army) const;
		bool operator != (const Army & army) const;

		void mutate();
		Army operator * (const Army & army) const;
};

#endif
