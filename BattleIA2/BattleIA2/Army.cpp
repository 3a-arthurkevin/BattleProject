#include "Army.h"

void Army::copyUnits(const std::vector<std::shared_ptr<Unit> >& units)
{
	_units.clear();
	for (auto it = units.begin(); it != units.end(); ++it)
		_units.push_back(std::shared_ptr<Unit>(new Unit(*(it->get()))));
}

void Army::copyUnits(const std::vector<std::shared_ptr<Unit> >& units, int nbElement)
{
	_units.clear();
	for (auto it = units.begin(); it != units.begin() + nbElement; ++it)
		_units.push_back(*it);
}

Army::Army(int size, int level)
{
	while (size--)
		_units.push_back(std::shared_ptr<Unit>(new Unit(level)));
}

Army::Army(std::vector<std::shared_ptr<Unit> >& units)
{
	copyUnits(units);
}


Army::Army(const Army& army)
{
	copyUnits(army._units);
}

void Army::swap(Army& army)
{
	std::swap(_units, army._units);
}

Army& Army::operator=(Army army)
{
	//swap(army);
	//*this = army;

	//_units = army._units;

	copyUnits(army._units);

	return *this;
}

Unit& Army::getUnit(int id)
{
	auto it = std::find_if(_units.begin(), _units.end(), [id](const std::shared_ptr<Unit>& unit) {
		return (unit->getId() == id);
	});
	if (it == _units.end())
		throw std::invalid_argument("wrong id : unit " + std::to_string(id) + " not found");

	return *(it->get());
}

Unit& Army::getNearestUnit(const Point& p)
{
	if (_units.empty())
		throw std::invalid_argument("empty army");
	
	Unit* result;
	float minDist = std::numeric_limits<float>::max();
	for (auto it = _units.begin(); it != _units.end(); ++it)
	{
		float d = (*it)->getPosition().distance(p);
		if (d < minDist)
		{
			minDist = d;
			result = it->get();
		}
	}
	return (*result);
}

Unit& Army::getFurthestUnit(const Point& p)
{
	if (_units.empty())
		throw std::invalid_argument("empty army");
	
	Unit* result;
	float maxDist = 0.0f;
	for (auto it = _units.begin(); it != _units.end(); ++it)
	{
		float d = (*it)->getPosition().distance(p);
		if (d > maxDist)
		{
			maxDist = d;
			result = it->get();
		}
	}
	return (*result);
}

Unit& Army::getLowestUnit(int capa_index)
{
	if (_units.empty())
		throw std::invalid_argument("empty army");
	
	/*
		min_element(first, last, func)
		func(T& a, T& b) --> comparator < beteen a and b (must return true if a < b)
	*/
	return **std::min_element(_units.begin(), _units.end(),
		[&capa_index](const std::shared_ptr<Unit>& a, const std::shared_ptr<Unit>& b) {
		return a->getCapacity(capa_index)->getLevel() < b->getCapacity(capa_index)->getLevel();
	});
}

Unit& Army::getHighestUnit(int capa_index)
{
	if (_units.empty())
		throw std::invalid_argument("empty army");
	
	/*
		max_element(first, last, func)
		func(T& a, T& b) --> comparator < beteen a and b (must return true if a < b)
	*/
	return **std::max_element(_units.begin(), _units.end(),
		[&capa_index](const std::shared_ptr<Unit>& a, const std::shared_ptr<Unit>& b) {
		return a->getCapacity(capa_index)->getLevel() < b->getCapacity(capa_index)->getLevel();
	});
}

void Army::purge()
{
	_units.erase(std::remove_if(_units.begin(), _units.end(), [](const std::shared_ptr<Unit>& u)
	{
		return !(u->isAlive());
	}), _units.end());
}



Army Army::mutate()const
{
	if (_units.size() == 0)
		return Army(*this);
	
	Army mutated(*this);
	int count = 1 + std::rand() % _units.size();
	while (count--) 
	{
		if (std::rand() % 3 == 0 || _units.size() == 1)
			mutated._units[std::rand() % _units.size()] = std::shared_ptr<Unit>(new Unit(_units[0]->getLevel()));
		else if (std::rand() % 2) 
		{
			int i1 = std::rand() % _units.size();
			int i2 = std::rand() % _units.size();
			while (i1 == i2)
				i2 = std::rand() % _units.size();
			mutated._units[i1] = std::shared_ptr<Unit>(new Unit(*(_units[i2])));
		}
		else 
		{
			int i1 = std::rand() % _units.size();
			int i2 = std::rand() % _units.size();
			while (i1 == i2)
				i2 = std::rand() % _units.size();
			mutated._units[i1] = std::shared_ptr<Unit>(new Unit((*(_units[i2]))*(*(_units[i1]))));
		}
	}
	return mutated;
}


Army Army::operator*(const Army& army)const
{
	if (this->size() == 0 && army.size() == 0)
		return Army(*this);
	
	int s = std::min(this->size(), army.size());
	std::vector<std::shared_ptr<Unit> > crossing;
	for (int i = 0; i < s; i++) 
	{
		switch (std::rand() % 4) 
		{
			case 0:
				crossing.push_back(std::shared_ptr<Unit>(new Unit(*(_units[i]))));
				break;
			case 1:
				crossing.push_back(std::shared_ptr<Unit>(new Unit(*(army._units[i]))));
				break;
			case 2:
				crossing.push_back(std::shared_ptr<Unit>(new Unit(*(_units[i])**(army._units[std::rand() % army._units.size()]))));
				break;
			case 3:
				crossing.push_back(std::shared_ptr<Unit>(new Unit(*(army._units[i])**(_units[std::rand() % _units.size()]))));
				break;
		}
	}
	return Army(crossing);
}


void Army::save(std::ostream& out)const
{
	std::for_each(_units.begin(), _units.end(), [&out](const std::shared_ptr<Unit>& unit) {
		unit->save(out);
	});
}

Army Army::load(std::istream& in)
{
	std::vector<std::shared_ptr<Unit> > units;

	in.exceptions(std::istream::failbit | std::istream::eofbit);
	while (in) 
	{
		try 
		{
			units.push_back(std::shared_ptr<Unit>(new Unit(Unit::load(in))));
		}
		catch (...) 
		{
			std::cout << "Catch - Army.cpp - load" << std::endl;
		}
	}
	return Army(units);
}

float Army::getAverageCapacityValue(int indexCapacity)
{
	try
	{ 
		if (_units.empty())
			throw std::invalid_argument("empty army");

		float sum = std::accumulate(_units.begin(), _units.end(), 0.0f,
			[indexCapacity](float& a, const std::shared_ptr<Unit>& b) {
			return ( a + b->getCapacity(indexCapacity)->getValue() );
		});

		return (sum / _units.size());
	}
	catch (...)
	{
		std::cout << "Catch - Army.cpp - getAverageCapacityValue" << std::endl;
		return 0.0f;
	}
}

float Army::getAverageDistance(Point point)
{
	try
	{
		if (_units.empty())
			throw std::invalid_argument("empty army");

		float sum = std::accumulate(_units.begin(), _units.end(), 0.0f,
			[point](float& a, const std::shared_ptr<Unit>& b) {
			return (a + (b->getPosition().distance(point)));
		});

		return (sum / _units.size());
	}
	catch (...) 
	{
		std::cout << "Catch - Army.cpp - getAverageDistance" << std::endl;
		return 0.0f;
	}
}

Point Army::getCentroid()
{
	try
	{
		if (_units.empty())
			throw std::invalid_argument("empty army");

		Point pointSum = std::accumulate(_units.begin(), _units.end(), Point(),
			[](Point& a, std::shared_ptr<Unit>& b){
			return (a + b->getPosition());
		});

		return (pointSum / (static_cast<float>(_units.size())));
	}
	catch (...) 
	{
		std::cout << "Catch - Army.cpp - getCentroid" << std::endl;
		return Point();
	}
}


Army Army::getNthLowestUnit(int nbElement, int indexCapacity)
{
	try
	{
		int nbUnit = _units.size();
		if (nbElement >= nbUnit)
			nbElement = nbUnit - 1;

		std::nth_element(_units.begin(), _units.begin() + nbElement, _units.end(),
			[indexCapacity](std::shared_ptr<Unit>& a, std::shared_ptr<Unit>& b){
			return (a->getCapacity(indexCapacity)->getLevel() < b->getCapacity(indexCapacity)->getLevel());
		});

		Army subArmy(0, 0);
		subArmy.copyUnits(_units, nbElement);

		return subArmy;
	}
	catch (...)
	{
		std::cout << "Catch - Army.cpp - getCentroid" << std::endl;
		return Army(0, 0);
	}
}

Army Army::getNthHighestUnit(int nbElement, int indexCapacity)
{
	try
	{
		int nbUnit = _units.size();
		if (nbElement >= nbUnit)
			nbElement = nbUnit - 1;

		std::nth_element(_units.begin(), _units.begin() + nbElement, _units.end(),
			[indexCapacity](std::shared_ptr<Unit>& a, std::shared_ptr<Unit>& b){
			return (a->getCapacity(indexCapacity)->getLevel() >= b->getCapacity(indexCapacity)->getLevel());
		});

		Army subArmy(0, 0);
		subArmy.copyUnits(_units, nbElement);

		return subArmy;
	}
	catch (...)
	{
		std::cout << "Catch - Army.cpp - getNthHighestUnit" << std::endl;
		return Army(0, 0);
	}
}


Army Army::getNthNearestUnit(int nbElement, Point point)
{
	try
	{
		int nbUnit = _units.size();
		if (nbElement >= nbUnit)
			nbElement = nbUnit - 1;

		std::nth_element(_units.begin(), _units.begin() + nbElement, _units.end(),
			[point](std::shared_ptr<Unit>& a, std::shared_ptr<Unit>& b){
			return (point.distance(a->getPosition()) < point.distance(b->getPosition()));
		});

		Army subArmy(0, 0);
		subArmy.copyUnits(_units, nbElement);

		return subArmy;
	}
	catch (...)
	{
		std::cout << "Catch - Army.cpp - getNthNearestUnit" << std::endl;
		return Army(0, 0);
	}
}

Army Army::getNthFurthestUnit(int nbElement, Point point)
{
	try
	{
		int nbUnit = _units.size();
		if (nbElement >= nbUnit)
			nbElement = nbUnit - 1;

		std::nth_element(_units.begin(), _units.begin() + nbElement, _units.end(),
			[point](std::shared_ptr<Unit>& a, std::shared_ptr<Unit>& b){
			return (point.distance(a->getPosition()) >= point.distance(b->getPosition()));
		});

		Army subArmy(0, 0);
		subArmy.copyUnits(_units, nbElement);

		return subArmy;
	}
	catch (...)
	{
		std::cout << "Catch - Army.cpp - getNthFurthestUnit" << std::endl;
		return Army(0, 0);
	}
}


Army Army::getSubArmyCapacityGreater(int indexCapacity, float threshold)
{
	if (_units.empty())
		std::cout << "Army Emplty - Army.cpp - getSubArmyCapacityGreater" << std::endl;

	Army subArmy(0, 0);
	for (auto it = _units.begin(); it != _units.end(); ++it)
	{
		if ((*it)->getCapacity(indexCapacity)->getValue() > threshold)
			subArmy._units.push_back(*it);
	}
	return subArmy;
}

Army Army::getSubArmyCapacitySmaller(int indexCapacity, float threshold)
{
	if (_units.empty())
		std::cout << "Army Emplty - Army.cpp - getSubArmyCapacitySmaller" << std::endl;

	Army subArmy(0, 0);
	for (auto it = _units.begin(); it != _units.end(); ++it)
	{
		if ((*it)->getCapacity(indexCapacity)->getValue() < threshold)
			subArmy._units.push_back(*it);
	}
	return subArmy;
}
