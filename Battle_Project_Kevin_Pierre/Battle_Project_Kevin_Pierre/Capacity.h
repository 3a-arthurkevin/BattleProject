#pragma once

#include "capacity.h"

class Capacity
{
	private:
		int _value;

	public:
		Capacity(void);
		~Capacity(void);
	
	protected:
		void Upgrade();
		void DownGrade();
		int GetLevel();
		const int GetValue() const;

};

