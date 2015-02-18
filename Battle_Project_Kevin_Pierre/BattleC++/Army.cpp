#include "Army.h"

Army::~Army(void)
{/*
	unsigned int i;
	unsigned int size = this->_units.size();

	for (i = 0; i < size; ++i)
		delete[] this->_units[i];
	*/
}

Army::Army(int nbUnit, int globalLevel)
{
	this->_units.reserve(nbUnit);
	int i;
	
	for (i = 0; i < nbUnit; ++i)
		this->_units.push_back(new Unit(globalLevel));
}

Army::Army(std::vector< Unit* > & units)
{
	unsigned int i;
	unsigned int size = units.size();

	for (i = 0; i < size; ++i)
	{
		this->_units.push_back(new Unit(units[i]->GetAiCode(),
										units[i]->GetSpeed().GetLevel(),
										units[i]->GetLifePoint().GetLevel(),
										units[i]->GetArmor().GetLevel(),
										units[i]->GetRegen().GetLevel(),
										units[i]->GetWeaponDamage().GetLevel(),
										units[i]->GetWeaponRange().GetLevel(),
										units[i]->GetWeaponSpeed().GetLevel()));
	}
}

std::vector< Unit* > & Army::GetUnitsList()
{
	return this->_units;
}

Unit * Army::GetUnit(unsigned int id)
{
	unsigned int indexUnit = 0;
	unsigned int size = this->_units.size();

	while (indexUnit < size)
	{
		if (this->_units[indexUnit]->GetId() == id)
			return (this->_units[indexUnit]);

		++indexUnit;
	}

	std::cout << "Error 404 - Unit with id " << id << " not found :(" << std::endl;
	return nullptr;
}

const int Army::Size() const
{
	return this->_units.size();
}

Unit * Army::GetNearestUnit(const Point & point) const
{
	if (this->_units.size() > 0)
	{
		Unit * nearestUnit = this->_units[0];
		float smallestDistance = nearestUnit->GetPosition().Distance(point);

		unsigned int i;
		unsigned int size = this->_units.size();

		for (i = 1; i < size; ++i)
		{
			if (this->_units[i]->GetPosition().Distance(point) < smallestDistance)
			{
				nearestUnit = this->_units[i];
				smallestDistance = nearestUnit->GetPosition().Distance(point);
			}
		}

		return nearestUnit;
	}
	
	std::cout << "Error - No Unit in this army" << std::endl;
	return nullptr;


}

Unit * Army::GetFarthestUnit(const Point& point) const
{
	if (this->_units.size() < 0)
	{
		Unit * nearestUnit = this->_units[0];
		float greatestDistance = nearestUnit->GetPosition().Distance(point);

		unsigned int i;
		unsigned int size = this->_units.size();

		for (i = 1; i < size; ++i)
		{
			if (this->_units[i]->GetPosition().Distance(point) > greatestDistance)
			{
				nearestUnit = this->_units[i];
				greatestDistance = nearestUnit->GetPosition().Distance(point);
			}
		}

		return nearestUnit;
	}

	std::cout << "Error - No Unit in this army" << std::endl;
	return nullptr;
}

Unit * Army::GetLowestUnit(int indexCapacity) const
{
	if (this->_units.size() < 0)
	{
		Unit * lowestUnit = this->_units[0];
		float lowestValue = (*lowestUnit)[indexCapacity].GetValue();

		unsigned int i;
		unsigned int size = this->_units.size();

		for (i = 1; i < size; ++i)
		{
			if ( (*(this->_units[i]))[indexCapacity].GetValue() < lowestValue )
			{
				lowestUnit = this->_units[i];
				lowestValue = (*lowestUnit)[indexCapacity].GetValue();
			}
		}
		return lowestUnit;
	}

	std::cout << "Error - No Unit in this army" << std::endl;
	return nullptr;
}

Unit * Army::GetHighestUnit(int indexCapacity) const
{
	if (this->_units.size() < 0)
	{
		Unit * highestUnit = this->_units[0];
		float highestValue = (*highestUnit)[indexCapacity].GetValue();

		unsigned int i;
		unsigned int size = this->_units.size();

		for (i = 1; i < size; ++i)
		{
			if ( (*(this->_units[i]))[indexCapacity].GetValue() < highestValue )
			{
				highestUnit = this->_units[i];
				highestValue = (*highestUnit)[indexCapacity].GetValue();
			}
		}
		return highestUnit;
	}

	std::cout << "Error - No Unit in this army" << std::endl;
	return nullptr;
}

void Army::Purge()
{
	auto iterator = std::begin(this->_units);
	unsigned int size = this->_units.size();

	while (iterator != std::end(this->_units))
	{
		if (! ((*iterator)->IsAlive()) )
			this->_units.erase(iterator);
		else
			++iterator;
	}
}

bool Army::operator < (const Army & army) const
{
	return (this->Size() < army.Size());
}

bool Army::operator > (const Army & army) const
{
	return (army < *this);
}

bool Army::operator >= (const Army & army) const
{
	return !(*this < army);
}

bool Army::operator <= (const Army & army)const
{
	return !(*this > army);
}

bool Army::operator == (const Army & army) const
{
	return !(*this < army || *this > army);
}

bool Army::operator != (const Army & army) const
{
	return (*this < army || *this > army);
}

void Army::mutate()
{
	//Choice between changing one unit and changing a part of army's units randomly
	int choice = rand() % 2;

	unsigned int indexUnit;

	if (choice == 0)
	{
		indexUnit = rand() % this->Size();

		*(this->_units[indexUnit]) = Unit(this->_units[indexUnit]->GetLevel());
	}
	else
	{
		unsigned int size = this->Size();
		unsigned int sizeFactor = 4; 
		
		unsigned int nbUnitToMutate = size / 4; // --> mutate 1/4 of the army
		unsigned int i;

		 for (i = 0; i < nbUnitToMutate; ++i)
		 {
			 indexUnit = rand() % size;
			 this->_units[indexUnit]->Mutate();
		 }
	}
}

Army Army::operator * (const Army & army) const
{
	std::vector< Unit* > newUnits;

	unsigned int indexUnitA;
	unsigned int indexUnitB;

	unsigned int sizeFactor = 3;
	unsigned int size = this->Size();

	unsigned int sizeA = size / sizeFactor;
	unsigned int sizeB = size / sizeFactor;
	unsigned int leftover = size - (sizeA + sizeB);

	unsigned int i;

	for (i = 0; i < sizeA; ++i)
	{
		indexUnitA = rand() % this->Size();
		
		newUnits.push_back(this->_units[indexUnitA]);
	}

	for (i = 0; i < sizeB; ++i)
	{
		indexUnitB = rand() % army.Size();

		newUnits.push_back(this->_units[indexUnitB]);
	}

	for (i = 0; i < leftover; ++i)
	{
		indexUnitA = rand() % this->Size();
		indexUnitB = rand() % army.Size();

		Unit newUnit = (*(this->_units[indexUnitA])) * (*(army._units[indexUnitB]));

		newUnits.push_back(new Unit(newUnit));
	}

	return Army(newUnits);
}