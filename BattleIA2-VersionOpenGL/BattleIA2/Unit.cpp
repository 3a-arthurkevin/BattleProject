#include "Unit.h"

//static counter used for unique id creation
int Unit::_idCount = 0;

//Method in charge of the initialization of id, position(random), and capacities
void Unit::init()
{
	_id = _idCount++;
	
	//this->_position = Point(static_cast<float>(std::rand() % 100), static_cast<float>(std::rand() % 100));
	this->_position = Point();
	
	this->_capacities.reserve(7);
	
	this->_capacities.push_back(std::unique_ptr<Capacity>(new SpeedCapacity()));
	this->_capacities.push_back(std::unique_ptr<Capacity>(new LifeCapacity()));
	this->_capacities.push_back(std::unique_ptr<Capacity>(new ArmorCapacity()));
	this->_capacities.push_back(std::unique_ptr<Capacity>(new RegenCapacity()));
	this->_capacities.push_back(std::unique_ptr<Capacity>(new DamageCapacity()));
	this->_capacities.push_back(std::unique_ptr<Capacity>(new RangeCapacity()));
	this->_capacities.push_back(std::unique_ptr<Capacity>(new FirerateCapacity()));
}

Unit::Unit(int globalLevel, std::string aiCode)
{
	init();

	_iaCode = aiCode;

	while (globalLevel--)
		this->_capacities[std::rand() % this->_capacities.size()]->upgrade();
}

//Constructor : global level will be randomly dispatched among the capacities
Unit::Unit(int globalLevel)
{
	init();

	if (std::rand() % 2)
		this->_iaCode = "L";
	else 
		this->_iaCode = "H";

	if (rand() % 8 == 0)
		this->_iaCode += "D";
	else 
		this->_iaCode += '0' + (char)(rand() % 7);

	while (globalLevel--)
		this->_capacities[std::rand() % this->_capacities.size()]->upgrade();
}


//Constructor from the code of AI and the level of the different capacities
Unit::Unit(std::string iaCode, int speedLevel, int lifeLevel, int armorLevel, int regenLevel, int damageLevel, int rangeLevel, int firerateLevel)
{
	init();

	_iaCode = iaCode;

	getSpeed().upgrade(speedLevel);
	getLife().upgrade(lifeLevel);
	getArmor().upgrade(armorLevel);
	getRegen().upgrade(regenLevel);
	getDamage().upgrade(damageLevel);
	getRange().upgrade(rangeLevel);
	getFirerate().upgrade(firerateLevel);
}


//Constructor from the code of AI and the level of the 7 capacities
Unit::Unit(std::string iaCode, std::vector<int>& levels)
{
	init();
	
	_iaCode = iaCode;

	for (unsigned int i = 0; i < levels.size() && i < _capacities.size(); ++i)
		_capacities[i]->upgrade(levels[i]);
}


//Copy constructor
Unit::Unit(const Unit& unit)
{
	init();

	//this->_id = unit._id;

	this->_iaCode = unit._iaCode;

	for (unsigned int i = 0; i < _capacities.size(); ++i)
		_capacities[i]->upgrade(unit._capacities[i]->getLevel());

	this->_position = unit._position;
}


//Swap the content of the parameter and the current object
void Unit::swap(Unit& unit)
{
	std::swap(_capacities, unit._capacities);
	std::swap(_iaCode, unit._iaCode);
	std::swap(_position, unit._position);
	std::swap(_id, unit._id);

}


//Assignment operator overload
Unit& Unit::operator=(Unit unit)
{
	swap(unit);
	return *this;
}


//Provide the global level of the unit (I.E. the sum of all capacities levels)
int Unit::getLevel()const
{
	/*
		accumulate(first, end, init, func)

		func signature : (const Type1 &a, const Type2 &b)
	*/
	return std::accumulate(_capacities.begin(), _capacities.end(), 0,
		[](int& a, const std::unique_ptr<Capacity>& b) {
		return a + b->getLevel();
	});
}


//Refresh the capacities of the unit, most often used at the beginning of fight turn.
//Reduce the cooldown of the firerate, and apply the regen on the life
void Unit::refresh()
{
	getLife().takeRegen(getRegen().getValue());
	getFirerate().reload();
}


//Make the unit shot if it is possible. In this case, the cooldown
//is set to maximum value and the method return true, otherwise, it return false.
bool Unit::shoot()
{
	if (getFirerate().canShoot())
	{
		getFirerate().shoot();
		return true;
	}
	return false;
}


//Apply the damages to the unit, by first reducing them by the armor,
//then apply it to the life.
void Unit::takeDamage(float value)
{
	getLife().takeDamage(value);
}


//Provide a randomly muteted version of the current unit
Unit Unit::mutate()const
{
	int index = std::rand() % 7;
	std::vector<int> levels(7);

	for (int i = 0; i < 7; ++i)
	{
		levels[i] = _capacities[i]->getLevel();
	}

	while (levels[index] == 0)
	{
		index = std::rand() % 7;
	}

	int index2 = std::rand() % 7;

	while (index == index2)
	{
		index2 = std::rand() % 7;
	}

	levels[index]--;
	levels[index2]++;
	return Unit(_iaCode, levels);
}


//Star operator overloading, providing a random crossing of the current
//unit and the one provided in parameter.
Unit Unit::operator*(const Unit& unit)const
{
	std::vector<int> maxLevels(7);
	for (int i = 0; i < 7; ++i)
	{
		maxLevels[i] = std::max(_capacities[i]->getLevel(), unit.getCapacity(i)->getLevel());
	}

	int gA = this->getLevel();
	int gB = unit.getLevel();
	int global = gA;

	if (gA != gB)
		global = std::min(gA, gB) + std::rand() % std::abs(gA - gB);

	std::vector<int> levels(7, 0);
	while (global)
	{
		int index = std::rand() % 7;
		if (levels[index]<maxLevels[index])
		{
			levels[index]++;
			global--;
		}
	}

	if (std::rand() % 2)
		return Unit(_iaCode, levels);

	return Unit(unit.getIACode(), levels);
}


//Save the current unit in the given output stream.
void Unit::save(std::ostream& out)const
{
	std::for_each(_capacities.begin(), _capacities.end(), [&out](const std::unique_ptr<Capacity>& c)
	{
		out << c->getLevel() << " ";
	});
	out << _iaCode << std::endl;
}


//Load a unit from the input stream
Unit Unit::load(std::istream& in)
{
	in.exceptions(std::istream::failbit | std::istream::eofbit);
	std::vector<int> levels(7);
	std::string iacode;
	std::for_each(levels.begin(), levels.end(), [&in](int& level)
	{
		in >> level;
	});
	in >> iacode;
	return Unit(iacode, levels);
}

