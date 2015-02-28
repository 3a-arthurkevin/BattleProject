#include "Unit.h"
#include "AI.h"

//Desctructor
Unit::~Unit(void)
{
}

/*
	First Constructor
		Using the random function to share the parameter's value (globalLevel between) the unit's capacities
*/
Unit::Unit(int globalLevel)
{
	//this->_levelMaxCap = globalLevel;
	this->_aiCode = AI::GetRandomAiCode();		// Giving a random Ai code with a static function from the class AI	
	this->_id = ++idCounter;					// Giving an unique id
	this->_hasPlayed = false;					// Giving the default value for the attribute _hasPlayed (false)

	/*
		incementing globalLevel as the random function has to give a value between 0 and globalLevel 
			--> if no incrementing, the random value given would be between 0 and (globalValue-1)
	*/
	++globalLevel;

	// Temporary variable that will be take the random value for level
	int level = 0;

	// Variables used to go out of the while loop if the randomly sharing of level is too long
	int nbIteration = 0;			
	int iterationMax = globalLevel;

	/*
		These variables will be used with the overrided opertor []
		In order to affect the random level value to a randomly chosen capacity between 0 and 6
	*/
	int indexCapacity = 0;
	int nbCapacity = 7;
	
	// Loop that will share globalLevel's value between the unit's capacities randomly
	while ( (globalLevel > 1) && (nbIteration < iterationMax) )
	{
		level = rand() % (globalLevel/2);
		globalLevel -= level;

		indexCapacity = rand() % nbCapacity;
		this->operator[](indexCapacity).SetLevel(level + this->operator[](indexCapacity).GetLevel());
		
		++nbIteration;
	}

	//decrementing of globalLevel as we don't need the random function
	--globalLevel;

	/*
		Case if the unit still has some globalLevel to share between its capacities after the while loop
			Giving the leftover to one capacity chosen randomly
	*/
	if (globalLevel > 0)
	{
		indexCapacity = rand() % nbCapacity;
		this->operator[](indexCapacity).SetLevel(globalLevel + this->operator[](indexCapacity).GetLevel());
	}

	this->_lifePoint.RegenMax();
}

/*
	Second Constructor
		Initialize the class attributes with the paramaters of the contructor
*/
Unit::Unit(const std::string IaCode, int speedLevel, int lifePointLevel, int armorLevel, int regenLevel, int weaponDamageLevel, int weaponRangeLevel, int weaponSpeedLevel)
{
	//this->_levelMaxCap = this->GetLevel();
	this->_id = ++idCounter;
	this->_aiCode = IaCode;
	this->_hasPlayed = false;

	this->_speed.SetLevel(speedLevel);
	this->_lifePoint.SetLevel(lifePointLevel);
	this->_armor.SetLevel(armorLevel);
	this->_regen.SetLevel(regenLevel);
	this->_weaponDamage.SetLevel(weaponDamageLevel);
	this->_weaponRange.SetLevel(weaponRangeLevel);
	this->_weaponSpeed.SetLevel(weaponSpeedLevel);

	this->_lifePoint.RegenMax();
}

/*
	Getter of the class attributes
*/
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

/*
	Overrinding of the bracket operator ( --> [])
		Return one of the unit's capacity (parameter value has to be between 0 and 6)
*/
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
			throw std::out_of_range("Error - index parameter out of range with operator [] for this instance of Unit class !!!");
			break;
	}
}

//Return the sum of all the unit's capacities levels
int Unit::GetLevel()
{
	int levelSum = 0;
	unsigned int nbCapacity = 7;
	unsigned int i;

	for (i = 0; i < nbCapacity; ++i)
		levelSum += this->operator[](i).GetLevel();
	
	return levelSum;
}

/*
	Getter of the unit's class attributes
*/
const Point & Unit::GetPosition() const
{
	return this->_position;
}

const std::string & Unit::GetAiCode() const
{
	return this->_aiCode;
}

/*
int Unit::GetLevelMaxCap() const
{
	return this->_levelMaxCap;
}
*/

bool Unit::GetHasPlayed() const
{
	return this->_hasPlayed;
}

/*
	Regen the LifePoint of the unit with the Regen value's capacity
	And calling the CoolDown method of WeaponSpeed capacity
	(Function used after a full turn of a battle)
*/
void Unit::Refresh()
{
	this->_lifePoint.RegenLife(this->_regen.GetValue());
	this->_weaponSpeed.CoolDown();
	this->_hasPlayed = false;
}

// Setter of the attribute _position
void Unit::SetPosition(const Point & point)
{
	this->_position.SetX(point.GetX());
	this->_position.SetY(point.GetY());

	this->_hasPlayed = true;
}

// Setter of the attribute _position
void Unit::SetPosition(float x, float y)
{
	this->_position.SetX(x);
	this->_position.SetY(y);

	this->_hasPlayed = true;
}

// Setter of the attribute _position (Used to initialized position at the begining of the battle)
void Unit::SetRandomPosition(const Point & point)
{
	this->_position.SetX(point.GetX());
	this->_position.SetY(point.GetY());
}

/*
	Check if WeaponSpeed _value equal 0 (if the unit can attack)
		if true --> _value = _maxValue the _hasPlayed = true and return true
		else	--> return false
*/
const bool Unit::Shoot()
{
	if (this->_weaponSpeed.GetValue() <= 0)
	{
		this->_weaponSpeed.WeaponUsed();
		this->_hasPlayed = true;

		return true;
	}
	
	return false;
}

/*
	Removing LifePoint _value
	The parameter value (damage) represente the damage given by an enemy's unit
	The function call ApplyDamage method from LifePoint's capacity
		--> the parameter passed to LifePoint's function called, is the damage given by the enemy minus the unit's Armor value
*/
void Unit::TakeDamage(float damage)
{
	float damageTotal = damage - this->_armor.GetValue();

	if (damageTotal > 0.f)
		this->_lifePoint.ApplyDamage(damageTotal);
}

/*
	Check if LifePoint's value of the unit is greather than 0
		return true if LifePoint's value > 0
		else return false
*/
bool Unit::IsAlive() const
{
	return (this->_lifePoint.GetValue() > 0.f);
}

/*
	Check if WeaponSpeed _value equal 0 (if the unit can attack)
		if true --> return true
		else return false
*/
bool Unit::CanShoot() const
{
	return (this->_weaponSpeed.GetValue() <= 0);
}

/*
	Find an index of capacity which is not level max
		--> the parameter index is an indx of capacity
		the parameter is an index of capacity not retunrable
*/
void Unit::Mutate()
{
	int indexToDownGrade = this->FindCapacity(-1);
	int indexToUpGrade = this->FindCapacity(indexToDownGrade);
	
	if ((indexToDownGrade >= 0 && indexToDownGrade <= 6) && (indexToUpGrade >= 0 && indexToUpGrade <= 6))
	{
		this->operator[](indexToDownGrade).DownGrade();

		this->operator[](indexToUpGrade).Upgrade();

		this->GetLifePoint().RegenMax();
	}
	else
		std::cout << "Can't mutate. Unit " << this->_id << std::endl;
}

/*
	Return a new Unit by "fusing" between 2 units
		--> overriding of the * operator
*/
const int Unit::FindCapacity(int index)
{
	int nbCapacityTotal = 7;

	//Try to find an index of capacity randomly
	unsigned int indexCapacity = 0;

	int nbIteration = 0;
	int iterationMax = 50;

	bool found = false;

	while (!found && (nbIteration < iterationMax) )
	{
		//Random between 0 and nbCapacity-1
		indexCapacity = rand() % nbCapacityTotal;

		if ( ((this->operator[](indexCapacity).GetLevel() > 0)) && (indexCapacity != index) )
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
			if ( ((this->operator[](indexCapacity).GetLevel() > 0)) && (indexCapacity != index) )
				return indexCapacity;

			++indexCapacity;
		}
	}

	//Default case
	return -1;
}

/*
	Return a new Unit by "fusing" between 2 units
		--> overriding of the * operator
*/
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

	//Instanciate child with this capacity of one of his parent (this)
	Unit child = Unit(iaCode,
		this->operator[](0).GetLevel(),
		this->operator[](1).GetLevel(),
		this->operator[](2).GetLevel(),
		this->operator[](3).GetLevel(),
		this->operator[](4).GetLevel(),
		this->operator[](5).GetLevel(),
		this->operator[](6).GetLevel());


	int i;
	int nbCapacity = 7;

	int maxLevel = this->GetLevel();

	for (i = 0; i < nbCapacity; ++i)
	{
		parent = rand() % 2;

		if (parent == 1)
		{
			child[i].SetLevel(unit[i].GetLevel());
		}
	}

	//Check if child level is between parents level and if each capacities level are between parents capacities level
	int indexRandomCapacity = 0;
	int iterationMax = 100;
	i = 0;

	//Get the max and min level 
	int minimumLevel = this->GetLevel() > unit.GetLevel() ? this->GetLevel() : unit.GetLevel();
	int maximumLevel = this->GetLevel() < unit.GetLevel() ? this->GetLevel() : unit.GetLevel();

	int capacityMaxLevel = 0;
	int capacityMinLevel = 0;
	int childCapacityLevel = 0;

	if (child.GetLevel() > maximumLevel)
	{
		while ((child.GetLevel() > maximumLevel) && (i < iterationMax))
		{
			indexRandomCapacity = rand() % nbCapacity;
			
			capacityMaxLevel = this->operator[](indexRandomCapacity).GetLevel() > unit.operator[](indexRandomCapacity).GetLevel() 
				? this->operator[](indexRandomCapacity).GetLevel() 
				: unit.operator[](indexRandomCapacity).GetLevel();
			
			capacityMinLevel = this->operator[](indexRandomCapacity).GetLevel() < unit.operator[](indexRandomCapacity).GetLevel() 
				? this->operator[](indexRandomCapacity).GetLevel() 
				: unit.operator[](indexRandomCapacity).GetLevel();
			
			childCapacityLevel = child.operator[](indexRandomCapacity).GetLevel();

			if ( (childCapacityLevel <= capacityMaxLevel) && (childCapacityLevel >= capacityMinLevel) )
				child.operator[](indexRandomCapacity).DownGrade();


			++i;
		}
	}
	else if (child.GetLevel() < minimumLevel)
	{ 
		while ((child.GetLevel() < maximumLevel) && ((i < iterationMax)))
		{
			indexRandomCapacity = rand() % nbCapacity;

			capacityMaxLevel = this->operator[](indexRandomCapacity).GetLevel() > unit.operator[](indexRandomCapacity).GetLevel() 
				? this->operator[](indexRandomCapacity).GetLevel() 
				: unit.operator[](indexRandomCapacity).GetLevel();
			
			capacityMinLevel = this->operator[](indexRandomCapacity).GetLevel() < unit.operator[](indexRandomCapacity).GetLevel() 
				? this->operator[](indexRandomCapacity).GetLevel() 
				: unit.operator[](indexRandomCapacity).GetLevel();

			childCapacityLevel = child.operator[](indexRandomCapacity).GetLevel();

			if ( (childCapacityLevel <= capacityMaxLevel) && (childCapacityLevel >= capacityMinLevel) )
				child.operator[](indexRandomCapacity).Upgrade();
			
			++i;
		}
	}

	return child;
}

//Set lifePoint of an Unit to 0
void Unit::Seppuku()
{
	this->_lifePoint.ApplyDamage(this->_lifePoint.GetMaxValue());
}