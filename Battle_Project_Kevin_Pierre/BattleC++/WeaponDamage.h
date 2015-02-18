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

		//Redéfiniton des la fonction dans la classe mère
		void ComputeValue();

		//Fonction de la classe mère avec ajout de code de la classe fille
		void Upgrade();
		void DownGrade();

		void SetLevel(int level);
};

#endif