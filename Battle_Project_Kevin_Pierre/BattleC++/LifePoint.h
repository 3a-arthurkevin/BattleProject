#ifndef LIFEPOINT_H
#define LIFEPOINT_H

#include "capacity.h"

class LifePoint  : 
	public Capacity
{
	private :
		//Attribut rep�sentant la valeur maximal des points de vie
		//La valeur des points de vie courants sont dans la classe m�re --> _value
		float _maxValue;

	public:
		//Destructeur
		~LifePoint(void);

		//Constructeur
		LifePoint(void);

		//Red�finiton des la fonction dans la classe m�re
		void ComputeValue();

		//Fonction de la classe m�re avec ajout de code de la classe fille
		void Upgrade();
		void DownGrade();

		void SetLevel(int level);

		//Getters et Setters  
		const float GetMaxValue() const;

		//Fonctions ajoutant et enlevant de la vie
		void RegenLife(float regen);
		void ApplyDamage(float damage);
};

#endif