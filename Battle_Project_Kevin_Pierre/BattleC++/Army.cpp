#include "Army.h"

//Destructor
Army::~Army(void)
{/*
	unsigned int i;
	unsigned int size = this->_units.size();

	for (i = 0; i < size; ++i)
		delete[] this->_units[i];
	*/
}

/*
	First Constructor
	Need the number of Unit in the army and the globalLevel for every Unit
		--> Use the first constructor of Unit's class
*/
Army::Army(int nbUnit, int globalLevel)
{
	this->_units.reserve(nbUnit);
	int i;
	
	for (i = 0; i < nbUnit; ++i)
		this->_units.push_back(new Unit(globalLevel));

	this->_score = 0;
}

/*
	Second Constructor
	Copy the vector in parameter
		--> Use the second constructor of Unit's class
*/
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

	this->_score = 0;
}

//Getter of _units
std::vector< Unit* > Army::GetUnitsList()
{
	return this->_units;
}

//Return an unit from _units who has the id in parameter
Unit & Army::GetUnit(int id)
{
	unsigned int indexUnit = 0;
	unsigned int size = this->_units.size();

	while (indexUnit < size)
	{
		if (this->_units[indexUnit]->GetId() == id)
			return (*(this->_units[indexUnit]));

		++indexUnit;
	}

	std::cout << "Error 404 - Unit with id " << id << " not found :(" << std::endl;
}

//Return the size of the vector _units
const int Army::Size() const
{
	return this->_units.size();
}

/*
	Functions returning the nearest and the farthest from a point
	By look the distance between the point and the position of every units in _units
*/
Unit & Army::GetNearestUnit(const Point & point)
{
	if (this->_units.size() > 0)
	{
		unsigned int indexNearestUnit = 0;
		float smallestDistance = (*(this->_units[indexNearestUnit])).GetPosition().Distance(point);

		unsigned int i;
		unsigned int size = this->_units.size();

		for (i = 1; i < size; ++i)
		{
			if (this->_units[i]->GetPosition().Distance(point) < smallestDistance)
			{
				indexNearestUnit = i;
				smallestDistance = (*(this->_units[indexNearestUnit])).GetPosition().Distance(point);
			}
		}

		return *(this->_units[indexNearestUnit]);
	}
	
	std::cout << "Error - No Unit in this army" << std::endl;
}

Unit & Army::GetFarthestUnit(const Point & point)
{
	if (this->_units.size() > 0)
	{
		unsigned int indexFarthestUnit = 0;
		float greatestDistance = (*(this->_units[indexFarthestUnit])).GetPosition().Distance(point);

		unsigned int i;
		unsigned int size = this->_units.size();

		for (i = 1; i < size; ++i)
		{
			if (this->_units[i]->GetPosition().Distance(point) > greatestDistance)
			{
				indexFarthestUnit = i;
				greatestDistance = (*(this->_units[indexFarthestUnit])).GetPosition().Distance(point);
			}
		}

		return *(this->_units[indexFarthestUnit]);
	}

	std::cout << "Error - No Unit in this army" << std::endl;
}

/*
	Functions returning the lowest and the highest according to the parameter which represente the index of a Unit's capacity
	By look the level of every units in _units
*/
Unit & Army::GetLowestUnit(int indexCapacity)
{
	if (this->_units.size() > 0)
	{
		unsigned int indexLowestUnit = 0;
		int lowestLevel = (*(this->_units[indexLowestUnit])).operator[](indexCapacity).GetLevel();

		unsigned int i;
		unsigned int size = this->_units.size();

		for (i = 1; i < size; ++i)
		{
			if ((*(this->_units[i]))[indexCapacity].GetLevel() < lowestLevel)
			{
				indexLowestUnit = i;
				lowestLevel = (*(this->_units[indexLowestUnit])).operator[](indexCapacity).GetLevel();
			}
		}
		return *(this->_units[indexLowestUnit]);
	}

	std::cout << "Error - No Unit in this army" << std::endl;
}

Unit & Army::GetHighestUnit(int indexCapacity)
{
	if (this->_units.size() > 0)
	{
		unsigned int indexHighestUnit = 0;
		int highestLevel = (*(this->_units[indexHighestUnit])).operator[](indexCapacity).GetLevel();

		unsigned int i;
		unsigned int size = this->_units.size();

		for (i = 1; i < size; ++i)
		{
			if ((*(this->_units[i]))[indexCapacity].GetLevel() > highestLevel)
			{
				indexHighestUnit = i;
				highestLevel = (*(this->_units[indexHighestUnit])).operator[](indexCapacity).GetLevel();
			}
		}
		return *(this->_units[indexHighestUnit]);
	}

	std::cout << "Error - No Unit in this army" << std::endl;
}

/*
	Looking for a unit who is have a LifePoint's value equal 0
		If an unit !IsAlive 
			--> removing this unit from the vector _units
*/
void Army::Purge()
{
	auto iterator = std::begin(this->_units);

	while (iterator != std::end(this->_units))
	{
		if (!((*iterator)->IsAlive()))
		{
			this->_units.erase(iterator);
			break;
		}
		else
			++iterator;
	}
}

//Apply Refresh() on all units --> see class Unit (function called after the end of a turn)
void Army::Refresh()
{
	auto iterator = std::begin(this->_units);

	while (iterator != std::end(this->_units))
	{
		(*iterator)->Refresh();
		++iterator;
	}
}

//Replace one unit by an other one generated randomly
void Army::Mutate()
{
	//Choice between changing one unit and changing a part of army's units randomly
	int choice = rand() % 2;

	unsigned int indexUnit;

	//Changing just one unit
	if (choice == 0)
	{
		indexUnit = rand() % this->Size();

		int globalLevel = this->GetUnitsList()[indexUnit]->GetLevel();

		this->GetUnitsList()[indexUnit]->Seppuku();
		this->Purge();
		this->AddNewUnit(globalLevel);
	}
	//Mutating a part of the army
	else
	{
		unsigned int size = this->Size();
		unsigned int sizeFactor = 1;
		
		if (size == 2)
			sizeFactor = 2;
		else if(size > 2)
			sizeFactor = 3;

		unsigned int nbUnitToMutate = size / sizeFactor; // --> mutate half of the army
		unsigned int i;

		for (i = 0; i < nbUnitToMutate; ++i)
		{
			indexUnit = rand() % size;
			this->_units[indexUnit]->Mutate();
		}
	}
}

//Add a new Unit randomly generated in the army
void Army::AddNewUnit(int globalLevel)
{
	this->_units.push_back(new Unit(globalLevel));
}

/*
	Mutation bewteen two Army --> Returning a new army composed with :
		--> a part of armyA's units
		--> a part of armyB's units
		--> units randomly generated to fill the empty space
*/
Army Army::operator * (const Army & army) const
{
	std::vector< Unit* > newUnits;

	unsigned int indexUnitA;
	unsigned int indexUnitB;

	unsigned int size = this->Size();
	unsigned int sizeFactor = 1;

	if (size == 2)
		sizeFactor = 2;
	else if (size > 2)
		sizeFactor = 3;

	unsigned int sizeA = size / sizeFactor;
	unsigned int sizeB = size / sizeFactor;
	unsigned int leftover = size - (sizeA + sizeB);

	unsigned int i;

	for (i = 0; i < sizeA; ++i)
	{
		indexUnitA = rand() % size;

		newUnits.push_back(this->_units[indexUnitA]);
	}

	for (i = 0; i < sizeB; ++i)
	{
		indexUnitB = rand() % size;

		newUnits.push_back(army._units[indexUnitB]);
	}

	for (i = 0; i < leftover; ++i)
	{
		indexUnitA = rand() % size;
		indexUnitB = rand() % size;

		Unit newUnit = (*(this->_units[indexUnitA])) * (*(army._units[indexUnitB]));

		newUnits.push_back(new Unit(newUnit));
	}

	return Army(newUnits);
}

/*
	Overinding of the comparisons operators for ordering
*/
bool Army::operator < (const Army & army) const
{
	return (this->_score < army._score);
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


/*
	Getter of the attribute _score
	Setters of the attribute _score
*/
int Army::GetScore() const
{
	return this->_score;
}

void Army::SetScore(const int score)
{
	this->_score = score;
}

void Army::AddScore(const int scoreToAdd)
{
	this->_score += scoreToAdd;
}

void Army::ResetScore()
{
	this->_score = 0;
}

//Return true if all units played else false
bool Army::CanPlay() const
{
	bool canPlay = false;

	int size = this->_units.size();
	int i = 0;
	
	while (!canPlay && i < size)
	{
		if (this->_units[i]->GetHasPlayed() == false)
			canPlay = true;
		++i;
	}

	return canPlay;
}

//Kill every unit of the army --> called when a battle is lasting more than 3000 turns
void Army::Kill()
{
	int size = this->_units.size();
	int i;

	for (i = 0; i < size; ++i)
	{
		this->_units[i]->Seppuku();
	}
	this->Purge();
}