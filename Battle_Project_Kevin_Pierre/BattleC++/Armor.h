#ifndef ARMOR_H
#define ARMOR_H

#include "capacity.h"
#include <iostream>

class Armor : public Capacity
{
	public:
		//Destructeur
		~Armor(void);

		//Constructeur
		Armor(void);

		//Redéfiniton de la fonction dans la classe mère
		void ComputeValue();

		//Fonction de la classe mère avec ajout de code de la classe fille
		void Upgrade();
		void DownGrade();

		void SetLevel(int level);
};

#endif