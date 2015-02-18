#ifndef WEAPONSPEED_H
#define WEAPONSPEED_H

#include "capacity.h"

class WeaponSpeed : 
	public Capacity
{
	private:
		//Attribut repésentant le
		float _maxValue;

	public:
		//Destructeur
		~WeaponSpeed(void);

		//Constructeur
		WeaponSpeed(void);

		//Redéfiniton des la fonction dans la classe mère
		void ComputeValue();

		//Fonction de la classe mère avec ajout de code de la classe fille
		void Upgrade();
		void DownGrade();

		void SetLevel(int level);

		//Getter et Setter
		const float GetMaxValue() const;

		//Fonction de diminution du cooldown de l'arme (décrémente _value)
		void CoolDown();

		//Fonction mettant à jour _value apres utilisation de l'arme
		void WeaponUsed();
};

#endif