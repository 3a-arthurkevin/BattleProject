#ifndef WEAPONSPEED_H
#define WEAPONSPEED_H

#include "capacity.h"

class WeaponSpeed : 
	public Capacity
{
	private:
		//Attribut rep�sentant le
		float _maxValue;

	public:
		//Destructeur
		~WeaponSpeed(void);

		//Constructeur
		WeaponSpeed(void);

		//Red�finiton des la fonction dans la classe m�re
		void ComputeValue();

		//Fonction de la classe m�re avec ajout de code de la classe fille
		void Upgrade();
		void DownGrade();

		void SetLevel(int level);

		//Getter et Setter
		const float GetMaxValue() const;

		//Fonction de diminution du cooldown de l'arme (d�cr�mente _value)
		void CoolDown();

		//Fonction mettant � jour _value apres utilisation de l'arme
		void WeaponUsed();
};

#endif