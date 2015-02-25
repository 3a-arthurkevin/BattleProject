#include "Action.h"

Action::~Action()
{
}

Action::Action()
{
	this->_action = ActionType::None;
	this->_id = -1;
}


const ActionType Action::GetAction() const
{
	return this->_action;
}

void Action::SetAction(ActionType action)
{
	this->_action = action;
}


const Point Action::GetLocation() const
{
	return this->_location;
}

void Action::SetLocation(const Point & point)
{
	this->_location.SetX(point.GetX());
	this->_location.SetY(point.GetY());
}

void Action::SetLocation(const float x, const float y)
{
	this->_location.SetX(x);
	this->_location.SetY(y);
}

int Action::GetId() const
{
	return this->_id;
}

void Action::SetId(int id)
{
	this->_id = id;
}
