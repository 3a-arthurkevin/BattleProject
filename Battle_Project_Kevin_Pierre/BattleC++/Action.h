#ifndef ACTION_H
#define ACTION_H

#include "Point.h"
#include "ActionType.h"


class Action
{
	private:
		ActionType _action;
		Point _location;
		int _id;

	public:
		//Destructor
		~Action();

		//Constructor
		Action();
		
		//Getter and Setter for the attribute _action (enum --> see ActionType.h)
		const ActionType GetAction() const;
		void SetAction(ActionType action);
		
		//Getter and Setter for the attribute _location (if the action is Flee or Move)
		const Point GetLocation() const;
		void SetLocation(const Point & point);
		void SetLocation(const float x, const float y);

		//Getter and Setter for the attribute _id (if the action is Shoot)
		int GetId() const;
		void SetId(int id);
};

#endif

