#include "Army.h"

void Army::copyUnits(const std::vector<std::shared_ptr<Unit> >& units)
{
	_units.clear();
	for (auto it = units.begin(); it != units.end(); ++it)
		_units.push_back(std::shared_ptr<Unit>(new Unit(*(it->get()))));
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
	swap(army);

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
	
	std::shared_ptr<Unit> result = std::shared_ptr<Unit>(_units[0]);
	float minDist = result->getPosition().distance(p);
	for (auto it = _units.begin()+1; it != _units.end(); ++it)
	{
		float d = (*it)->getPosition().distance(p);
		if (d < minDist)
		{
			minDist = d;
			result = *it;
		}
	}
	return (*result);
}

Unit& Army::getFurthestUnit(const Point& p)
{
	if (_units.empty())
		throw std::invalid_argument("empty army");
	
	std::shared_ptr<Unit> result = std::shared_ptr<Unit>(_units[0]);
	float maxDist = result->getPosition().distance(p);
	for (auto it = _units.begin()+1; it != _units.end(); ++it)
	{
		float d = (*it)->getPosition().distance(p);
		if (d > maxDist)
		{
			maxDist = d;
			result = *it;
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