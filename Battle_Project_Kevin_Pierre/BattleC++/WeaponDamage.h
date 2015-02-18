#ifndef WEAPONDAMAGE_H
#define WEAPONDAMAGE_H

#include "capacity.h"

class WeaponDamage : 
	public Capacity
{
	public:
		//Destructeur
		~WeaponDamage(void);

		//Constructeur
		WeaponDamage(void);

		//Red�finiton des la fonction dans la classe m�re
		void ComputeValue();

		//Fonction de la classe m�re avec ajout de code de la classe fille
		void Upgrade();
		void DownGrade();

		void SetLevel(int level);
};

#endif