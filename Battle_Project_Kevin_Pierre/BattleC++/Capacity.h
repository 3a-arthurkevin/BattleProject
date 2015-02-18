#ifndef CAPACITY_H
#define CAPACITY_H

/*
	Classe abstraite car il y a au moins une fonction vituelle pure --> Upgrade / DownGrade
		Donc On ne peut pas instancier ni passer en param�tre ni retourner un Capacity !!!
		(Slide 26 cours)
*/

class Capacity
{
	protected:
		/*
			Attributs
		*/

		//Attributs repr�sentant respectivement le niveau et la valeur d'une capacit�
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

		//Fonction qui effectuera le calcul de la valeur d'une capacit�
			//--> Virtual car impl�mentation dans les classes d�riv�es (non virtuel pur pour pouvoir red�finir op�rateur dans Unit --> accesseur capacities avec [])
		virtual void ComputeValue();

		//Fonctions incr�mentant et d�crementant le niveau r�spectivement
		void Upgrade();
		void DownGrade();

		//Getter r�cup�rant _level et _value respectivement
		const int GetLevel() const;
		const float GetValue() const;

		//Setter affectant un niveau --> a besoin du calcul apres affectation du niveau ()
			//--> Virtual car impl�mentation dans les classes d�riv�es
		virtual void SetLevel(int level);
};

#endif