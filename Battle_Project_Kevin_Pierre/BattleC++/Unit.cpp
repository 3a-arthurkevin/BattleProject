#include "Unit.h"
#include "AI.h"

Unit::~Unit(void)
{
}

Unit::Unit(int globalLevel)
{
	this->_levelMaxCap = globalLevel;
	//incémentation de globalLevel pour avoir le bon niveau global et non globalLevel-1 niveau 
		//--> Car rand() prend un valeur de 0 à globalLevel-1
	++globalLevel;

	int level = 0;

	unsigned int nbIteration = 0;
	unsigned int iterationMax = 100;

	unsigned int indexCapacity = 0;
	unsigned int nbCapacityTotal = 7;
	
	while (globalLevel > 1 && nbIteration < iterationMax)
	{
		//Random entre 0 et globalLevel-1
		level = rand() % globalLevel;
		globalLevel -= level;

		indexCapacity = rand() % nbCapacityTotal;
		this->operator[](indexCapacity).SetLevel(level + this->operator[](indexCapacity).GetLevel());
		
		++nbIteration;
	}

	//décrementation de globalLevel pour contre balancer l'incrémentation ci-dessus car on n'utilise plus rand();
	--globalLevel;

	//Cas ou on n'aurait pas attribuer suffisamment de niveaux pour que l'unité soit de globalLevel (à cause du rand())
	if (globalLevel > 0)
	{
		indexCapacity = rand() % nbCapacityTotal;
		this->operator[](indexCapacity).SetLevel(globalLevel + this->operator[](indexCapacity).GetLevel());
	}

	this->_aiCode = AI::GetRandomIaCode();

	this->_id = ++idCounter;
}

Unit::Unit(const std::string & IaCode, int speedLevel, int lifePointLevel, int armorLevel, int regenLevel, int weaponDamageLevel, int weaponRangeLevel, int weaponSpeedLevel)
{
	this->_id = ++idCounter;
	this->_aiCode = IaCode;

	this->_speed.SetLevel(speedLevel);
	this->_lifePoint.SetLevel(lifePointLevel);
	this->_armor.SetLevel(armorLevel);
	this->_regen.SetLevel(regenLevel);
	this->_weaponDamage.SetLevel(weaponDamageLevel);
	this->_weaponRange.SetLevel(weaponRangeLevel);
	this->_weaponSpeed.SetLevel(weaponSpeedLevel);

	this->_levelMaxCap = this->GetLevel();
}


const int Unit::GetId() const
{
	return this->_id;
}

Speed & Unit::GetSpeed()
{
	return this->_speed;
}

LifePoint & Unit::GetLifePoint()
{
	return this->_lifePoint;
}

Armor & Unit::GetArmor()
{
	return this->_armor;
}

Regen & Unit::GetRegen()
{
	return this->_regen;
}

WeaponDamage & Unit::GetWeaponDamage()
{
	return this->_weaponDamage;
}

WeaponRange & Unit::GetWeaponRange()
{
	return this->_weaponRange;
}

WeaponSpeed & Unit::GetWeaponSpeed()
{
	return this->_weaponSpeed;
}

Capacity & Unit::operator [](unsigned int value)
{
	switch (value)
	{
		case 0:
			return (this->_speed);
		case 1:
			return (this->_lifePoint);
		case 2:
			return (this->_armor);
		case 3:
			return (this->_regen);
		case 4:
			return (this->_weaponDamage);
		case 5:
			return (this->_weaponRange);
		case 6:
			return (this->_weaponSpeed);
		default:
			throw std::out_of_range("Erreur avec l'index donné dans l'opérateur [] pour une instance de la classe Unit !!!");
			break;
	}
}

int Unit::GetLevel()
{
	int levelSum = 0;
	unsigned int nbCapacity = 7;
	unsigned int i;

	for (i = 0; i < nbCapacity; ++i)
		levelSum += this->operator[](i).GetLevel();
	
	return levelSum;
}

const Point & Unit::GetPosition() const
{
	return this->_position;
}

const std::string & Unit::GetAiCode() const
{
	return this->_aiCode;
}

int Unit::GetLevelMaxCap() const
{
	return this->_levelMaxCap;
}


void Unit::Refresh()
{
	this->_lifePoint.RegenLife(this->_regen.GetValue());
	this->_weaponSpeed.CoolDown();
}

void Unit::SetPosition(const Point & point)
{
	this->_position.SetX(point.GetX());
	this->_position.SetY(point.GetY());
}

const bool Unit::Shoot()
{
	if (this->_weaponSpeed.GetValue() == 0)
	{
		this->_weaponSpeed.WeaponUsed();
		return true;
	}
	
	return false;
}

void Unit::TakeDamage(float damage)
{
	this->_lifePoint.ApplyDamage(damage - this->_armor.GetValue());
}

bool Unit::IsAlive() const
{
	return (this->_lifePoint.GetValue() > 0);
}

bool Unit::CanShoot() const
{
	return (this->_weaponSpeed.GetValue() == 0);
}


void Unit::Mutate()
{
	int indexToDownGrade = this->findCapacityNotCaped(-1);
	int indexToUpGrade = this->findCapacityNotCaped(indexToDownGrade);

	std::cout << indexToDownGrade << " | " << indexToUpGrade << std::endl;
	
	if ((indexToDownGrade >= 0 && indexToDownGrade <= 6) && (indexToUpGrade >= 0 && indexToUpGrade <= 6))
	{
		this->operator[](indexToDownGrade).DownGrade();

		this->operator[](indexToUpGrade).Upgrade();
	}
	else
		std::cout << "Can't mutate. Unit " << this->_id << std::endl;
}

const int Unit::findCapacityNotCaped(int index)
{
	int nbCapacityTotal = 7;

	//Check if unit is level max in all capacities
	if (this->GetLevel() < (this->_levelMaxCap * (nbCapacityTotal - 1)))
	{
		//Try to find an index of capacity not maxed randomly
		unsigned int indexCapacity = 0;

		int nbIteration = 0;
		int iterationMax = 50;

		bool found = false;

		while (!found && nbIteration < iterationMax)
		{
			//Random entre 0 et nbCapacity-1
			indexCapacity = rand() % nbCapacityTotal;

			if ( ((this->operator[](indexCapacity).GetLevel() < this->_levelMaxCap) && (this->operator[](indexCapacity).GetLevel() > 0)) && (indexCapacity != index) )
				return indexCapacity;

			++nbIteration;
		}

		//Case where random find didn't get any index
		//Try to find an index of capacity not maxed from capacity n°0 to n°(nbCapacityTotal-1)
		if (nbIteration >= iterationMax && !found)
		{
			found = false;
			int indexCapacity = 0;

			while (!found && indexCapacity < (nbCapacityTotal - 1))
			{
				if ( ((this->operator[](indexCapacity).GetLevel() < this->_levelMaxCap) && (this->operator[](indexCapacity).GetLevel() > 0)) && (indexCapacity != index))
					return indexCapacity;

				++indexCapacity;
			}
		}
	}

	//Case unit is level max --> return an int < 0
	return -1;
}

Unit Unit::operator*(Unit & unit)
{
	//Get the Ai code of a parent
	std::string iaCode = "";
	int parent;

	parent = rand() % 2;

	if (parent == 0)
		iaCode = this->_aiCode;
	else
		iaCode = unit._aiCode;

	//Instanciate child with this capacity
	Unit child = Unit(iaCode,
		this->operator[](0).GetLevel(),
		this->operator[](1).GetLevel(),
		this->operator[](2).GetLevel(),
		this->operator[](3).GetLevel(),
		this->operator[](4).GetLevel(),
		this->operator[](5).GetLevel(),
		this->operator[](6).GetLevel());


	unsigned int i;
	unsigned int nbCapacity = 7;

	//Get the max and min level 
	int minimumLevel = this->GetLevel() > unit.GetLevel() ? this->GetLevel() : unit.GetLevel();
	int maximumLevel = this->GetLevel() < unit.GetLevel() ? this->GetLevel() : unit.GetLevel();

	for (i = 0; i < nbCapacity; ++i)
	{
		parent = rand() % 2;

		if (parent == 1)
		{
			child[i].SetLevel(unit[i].GetLevel());
		}
	}

	//Check if child level is between parents level and if each capatiies level are between parents capacities level
	int childLevel = child.GetLevel();
	unsigned indexRandomCapacity = 0;
	int iterationMax = 50;
	i = 0;

	int capacityMaxLevel;
	int capacityMinLevel;
	int childCapacityLevel;

	if (childLevel > maximumLevel)
	{
		while ((childLevel > maximumLevel) && (i < iterationMax))
		{
			indexRandomCapacity = rand() % nbCapacity;
			
			capacityMaxLevel = this->operator[](indexRandomCapacity).GetLevel() > unit.operator[](indexRandomCapacity).GetLevel() ? this->operator[](indexRandomCapacity).GetLevel() : unit.operator[](indexRandomCapacity).GetLevel();
			capacityMinLevel = this->operator[](indexRandomCapacity).GetLevel() < unit.operator[](indexRandomCapacity).GetLevel() ? this->operator[](indexRandomCapacity).GetLevel() : unit.operator[](indexRandomCapacity).GetLevel();
			
			childCapacityLevel = child.operator[](indexRandomCapacity).GetLevel();

			if ((childCapacityLevel > 0) && (childCapacityLevel < capacityMaxLevel && childCapacityLevel > capacityMinLevel))
				child.operator[](indexRandomCapacity).DownGrade();

			++i;
		}
	}
	else if (childLevel < minimumLevel)
	{ 
		while ((childLevel < maximumLevel) && ((i < iterationMax)))
		{
			indexRandomCapacity = rand() % nbCapacity;

			capacityMaxLevel = this->operator[](indexRandomCapacity).GetLevel() > unit.operator[](indexRandomCapacity).GetLevel() ? this->operator[](indexRandomCapacity).GetLevel() : unit.operator[](indexRandomCapacity).GetLevel();
			capacityMinLevel = this->operator[](indexRandomCapacity).GetLevel() < unit.operator[](indexRandomCapacity).GetLevel() ? this->operator[](indexRandomCapacity).GetLevel() : unit.operator[](indexRandomCapacity).GetLevel();

			childCapacityLevel = child.operator[](indexRandomCapacity).GetLevel();

			if ( (childCapacityLevel < child._levelMaxCap) && (childCapacityLevel < capacityMaxLevel && childCapacityLevel > capacityMinLevel))
				child.operator[](indexRandomCapacity).Upgrade();
			
			++i;
		}
	}

	return child;
}