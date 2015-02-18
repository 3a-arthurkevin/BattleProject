#ifndef REGEN_H
#define REGEN_H

#include "capacity.h"

class Regen : 
	public Capacity
{
	public:
		//Desctructeur
		~Regen(void);

		//Constructeur
		Regen(void);

		//Redéfiniton des la fonction dans la classe mère
		void ComputeValue();

		//Fonction de la classe mère avec ajout de code de la classe fille
		void Upgrade();
		void DownGrade();

		void SetLevel(int level);
};

#endif