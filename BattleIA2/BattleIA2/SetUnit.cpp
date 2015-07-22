#include "SetUnit.h"

SetUnit::SetUnit()
{

}

SetUnit::SetUnit(const SetUnit& setUnit)
{
	copySetUnit(setUnit._setUnit);
}

SetUnit SetUnit::copySetUnit()
{
	SetUnit SetToCopy;

	for (auto it = _setUnit.begin(); it != _setUnit.end(); ++it)
		SetToCopy._setUnit.push_back(*it);

	return SetToCopy;
}

SetUnit SetUnit::copySubSetUnit(const std::vector<std::shared_ptr<Unit> >& units, int nbElement)
{
	SetUnit SetToCopy;

	for (auto it = _setUnit.begin(); it != _setUnit.begin() + nbElement; ++it)
		SetToCopy._setUnit.push_back(*it);

	return SetToCopy;
}

void SetUnit::copySetUnit(const std::vector<std::shared_ptr<Unit> >& units)
{
	_setUnit.clear();

	for (auto it = units.begin(); it != units.end(); ++it)
		_setUnit.push_back(*it);
}

void SetUnit::swap(SetUnit& setUnit)
{
	std::swap(_setUnit, setUnit._setUnit);
}

SetUnit& SetUnit::operator = (SetUnit setUnit)
{
	swap(setUnit);
	return *this;
}

SetUnit::SetUnit(std::vector< std::shared_ptr<Unit> > unitVector)
{
	_setUnit.clear();

	for (auto it = unitVector.begin(); it != unitVector.end(); ++it)
		_setUnit.push_back(*it);
}

Unit& SetUnit::getNearestUnit(const Point& p)
{
	if (_setUnit.empty())
		throw std::invalid_argument("getNearestUnit - Empty Set");

	std::shared_ptr<Unit> result = std::shared_ptr<Unit>(_setUnit[0]);
	float minDist = result->getPosition().distance(p);
	for (auto it = _setUnit.begin() + 1; it != _setUnit.end(); ++it)
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

Unit& SetUnit::getFurthestUnit(const Point& p)
{
	if (_setUnit.empty())
		throw std::invalid_argument("getFurthestUnit - Empty Set");

	std::shared_ptr<Unit> result = std::shared_ptr<Unit>(_setUnit[0]);
	float maxDist = result->getPosition().distance(p);
	for (auto it = _setUnit.begin() + 1; it != _setUnit.end(); ++it)
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

Unit& SetUnit::getLowestUnit(int capa_index)
{
	if (_setUnit.empty())
		throw std::invalid_argument("getLowestUnit - Empty Set");

	/*
	min_element(first, last, func)
	func(T& a, T& b) --> comparator < beteen a and b (must return true if a < b)
	*/
	return **std::min_element(_setUnit.begin(), _setUnit.end(),
		[&capa_index](const std::shared_ptr<Unit>& a, const std::shared_ptr<Unit>& b) {
		return a->getCapacity(capa_index)->getLevel() < b->getCapacity(capa_index)->getLevel();
	});
}

Unit& SetUnit::getHighestUnit(int capa_index)
{
	if (_setUnit.empty())
		throw std::invalid_argument("getHighestUnit - Empty Set");

	/*
	max_element(first, last, func)
	func(T& a, T& b) --> comparator < beteen a and b (must return true if a < b)
	*/
	return **std::max_element(_setUnit.begin(), _setUnit.end(),
		[&capa_index](const std::shared_ptr<Unit>& a, const std::shared_ptr<Unit>& b) {
		return a->getCapacity(capa_index)->getLevel() < b->getCapacity(capa_index)->getLevel();
	});
}

float SetUnit::getAverageCapacityValue(int indexCapacity)
{
	if (_setUnit.empty())
		throw std::invalid_argument("getAverageCapacityValue - Empty set");

	float sum = std::accumulate(_setUnit.begin(), _setUnit.end(), 0.0f,
		[indexCapacity](float& a, const std::shared_ptr<Unit>& b) {
		return (a + b->getCapacity(indexCapacity)->getValue());
	});

	return (sum / _setUnit.size());
}

float SetUnit::getAverageDistance(Point point)
{
	if (_setUnit.empty())
		throw std::invalid_argument("getAverageDistance - Empty set");

	float sum = std::accumulate(_setUnit.begin(), _setUnit.end(), 0.0f,
		[point](float& a, const std::shared_ptr<Unit>& b) {
		return (a + (b->getPosition().distance(point)));
	});

	return (sum / _setUnit.size());
}

Point SetUnit::getCentroid()
{

	if (_setUnit.empty())
		throw std::invalid_argument("getCentroid - Empty set");

	Point pointSum = std::accumulate(_setUnit.begin(), _setUnit.end(), Point(),
		[](Point& a, std::shared_ptr<Unit>& b){
		return (a + b->getPosition());
	});

	return (pointSum / (static_cast<float>(_setUnit.size())));
}


SetUnit SetUnit::getNthLowestUnit(int nbElement, int indexCapacity)
{
	if (_setUnit.empty())
		throw std::invalid_argument("getNthLowestUnit - Empty set");

	int nbUnit = _setUnit.size();

	if (nbElement >= nbUnit)
		return SetUnit(*this);

	std::nth_element(_setUnit.begin(), _setUnit.begin() + nbElement, _setUnit.end(),
		[indexCapacity](std::shared_ptr<Unit>& a, std::shared_ptr<Unit>& b){
		return (a->getCapacity(indexCapacity)->getLevel() < b->getCapacity(indexCapacity)->getLevel());
	});

	return copySubSetUnit(_setUnit, nbElement);
}

SetUnit SetUnit::getNthHighestUnit(int nbElement, int indexCapacity)
{
	if (_setUnit.empty())
		throw std::invalid_argument("Empty army - getNthHighestUnit");

	int nbUnit = _setUnit.size();

	if (nbElement >= nbUnit)
		return SetUnit(*this);

	std::nth_element(_setUnit.begin(), _setUnit.begin() + nbElement, _setUnit.end(),
		[indexCapacity](std::shared_ptr<Unit>& a, std::shared_ptr<Unit>& b){
		return (b->getCapacity(indexCapacity)->getLevel() < a->getCapacity(indexCapacity)->getLevel());
	});

	return copySubSetUnit(_setUnit, nbElement);
}


SetUnit SetUnit::getNthNearestUnit(int nbElement, Point point)
{
	if (_setUnit.empty())
		throw std::invalid_argument("Empty army - getNthNearestUnit");

	int nbUnit = _setUnit.size();

	if (nbElement >= nbUnit)
		return SetUnit(*this);

	std::nth_element(_setUnit.begin(), _setUnit.begin() + nbElement, _setUnit.end(),
		[point](std::shared_ptr<Unit>& a, std::shared_ptr<Unit>& b){
		return (point.distance(a->getPosition()) < point.distance(b->getPosition()));
	});

	return copySubSetUnit(_setUnit, nbElement);
}

SetUnit SetUnit::getNthFurthestUnit(int nbElement, Point point)
{
	if (_setUnit.empty())
		throw std::invalid_argument("Empty army - getNthFurthestUnit");

	int nbUnit = _setUnit.size();

	if (nbElement >= nbUnit)
		return SetUnit(*this);

	std::nth_element(_setUnit.begin(), _setUnit.begin() + nbElement, _setUnit.end(),
		[point](std::shared_ptr<Unit>& a, std::shared_ptr<Unit>& b){
		return (point.distance(b->getPosition()) < point.distance(a->getPosition()));
	});

	return copySubSetUnit(_setUnit, nbElement);
}


SetUnit SetUnit::getSubArmyCapacityGreater(int indexCapacity, float threshold)
{
	if (_setUnit.empty())
		throw std::invalid_argument("Empty army - getNthFurthestUnit");

	SetUnit setToReturn;

	for (auto it = _setUnit.begin(); it != _setUnit.end(); ++it)
	{
		if ((*it)->getCapacity(indexCapacity)->getValue() > threshold)
			setToReturn._setUnit.push_back(*it);
	}
	return setToReturn;
}

SetUnit SetUnit::getSubArmyCapacitySmaller(int indexCapacity, float threshold)
{
	if (_setUnit.empty())
		throw std::invalid_argument("Empty army - getNthFurthestUnit");

	SetUnit setToReturn;

	for (auto it = _setUnit.begin(); it != _setUnit.end(); ++it)
	{
		if ((*it)->getCapacity(indexCapacity)->getValue() < threshold)
			setToReturn._setUnit.push_back(*it);
	}

	return setToReturn;
}