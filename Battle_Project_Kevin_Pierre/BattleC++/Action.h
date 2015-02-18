#ifndef ACTION_H
#define ACTION_H

#include "Point.h"
#include "ActionType.h"


class Action
{
	private:
		ActionType _action;
		Point _location;
		unsigned int _id;

	public:
		//Desctructeur
		~Action();

		//Constructeur
		Action();
		
		const ActionType GetAction() const;
		void SetAction(ActionType action);
		
		const Point GetLocation() const;
		void SetLocation(const Point & point);

		const unsigned int GetId() const;
		void SetId(unsigned id);

};

#endif

