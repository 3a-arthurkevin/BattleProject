#ifndef WEAPONRANGE_H
#define WEAPONRANGE_H

#include "capacity.h"

class WeaponRange :
	public Capacity
{
	public:
		//Destructeur
		~WeaponRange(void);

		//Constructeur
		WeaponRange(void);

		//Red�finiton des la fonction dans la classe m�re
		void ComputeValue();

		//Fonction de la classe m�re avec ajout de code de la classe fille
		void Upgrade();
		void DownGrade();

		void SetLevel(int level);
};

#endif