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

		//Redéfiniton des la fonction dans la classe mère
		void ComputeValue();

		//Fonction de la classe mère avec ajout de code de la classe fille
		void Upgrade();
		void DownGrade();

		void SetLevel(int level);
};

#endif