#ifndef SPEED_H
#define SPEED_H

#include "capacity.h"

class Speed  : 
	public Capacity
{
	public:
		//Desctructeur
		~Speed(void);

		//Constructeur
		Speed(void);

		//Redéfiniton des la fonction dans la classe mère
		void ComputeValue();

		//Fonction de la classe mère avec ajout de code de la classe fille
		void Upgrade();
		void DownGrade();

		void SetLevel(int level);
};

#endif