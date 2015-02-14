#pragma once

#include "capacity.h"

/*
	Classe abstraite car il y a au moins une fonction vituelle pure --> Upgrade / DownGrade
		Donc On ne peut pas instancier ni passer en paramètre ni retourner un Capacity !!!
		(Slide 26 cours)
*/

class Capacity
{
	protected:
		int _level;
		float _value;

	public:
		virtual ~Capacity(void);

		Capacity(void);

		virtual void Upgrade() = 0;
		virtual void DownGrade() = 0;

		const int GetLevel() const;
		const float GetValue() const;
};

