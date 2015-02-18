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

		//Red�finiton des la fonction dans la classe m�re
		void ComputeValue();

		//Fonction de la classe m�re avec ajout de code de la classe fille
		void Upgrade();
		void DownGrade();

		void SetLevel(int level);
};

#endif