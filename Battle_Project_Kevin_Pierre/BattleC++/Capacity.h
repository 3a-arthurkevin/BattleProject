#ifndef CAPACITY_H
#define CAPACITY_H

/*
	Classe abstraite car il y a au moins une fonction vituelle pure --> Upgrade / DownGrade
		Donc On ne peut pas instancier ni passer en paramètre ni retourner un Capacity !!!
		(Slide 26 cours)
*/

class Capacity
{
	protected:
		/*
			Attributs
		*/

		//Attributs représentant respectivement le niveau et la valeur d'une capacité
		int _level;
		float _value;

	public:
		/*
			Fonctions
		*/

		//Desctructeur
		~Capacity(void);

		//Constructeur
		Capacity(void);

		//Fonction qui effectuera le calcul de la valeur d'une capacité
			//--> Virtual car implémentation dans les classes dérivées (non virtuel pur pour pouvoir redéfinir opérateur dans Unit --> accesseur capacities avec [])
		virtual void ComputeValue();

		//Fonctions incrémentant et décrementant le niveau réspectivement
		void Upgrade();
		void DownGrade();

		//Getter récupérant _level et _value respectivement
		const int GetLevel() const;
		const float GetValue() const;

		//Setter affectant un niveau --> a besoin du calcul apres affectation du niveau ()
			//--> Virtual car implémentation dans les classes dérivées
		virtual void SetLevel(int level);
};

#endif