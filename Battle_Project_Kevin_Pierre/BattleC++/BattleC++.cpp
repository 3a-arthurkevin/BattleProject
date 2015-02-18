// BattleC++.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

#include <algorithm>

#include <iostream>

#include <time.h>

#include "AI.h"


int _tmain(int argc, _TCHAR* argv[])
{
	//Initialisation du random pour que ca ne fasse pas la même chose à chaque Run (à ne faire qu'un fois dans le code)
	srand((unsigned int)time(NULL));
	
	int I, T, N, X, Y;
	std::cout << "Iteration : ";
	std::cin >> I; // --> nb Iteration

	std::cout << "Score criteria : ";
	std::cin >> T; // --> army criteria
	
	std::cout << "Nb army : ";
	std::cin >> N; // --> nb Army
	
	std::cout << "Nb Unit : ";
	std::cin >> X; // --> nb Unit
	
	std::cout << "Global level : ";
	std::cin >> Y; // --> global level

	std::vector<Army> armiesVector;

	int i;
	int x = 0;
	for (i = 0; i < N; ++i)
	{
		std::cout << i << std::endl;
		armiesVector.push_back(Army(++x, Y));
	}
	for (i = 0; i < N; ++i)
		std::cout << armiesVector[i].Size() << std::endl;

	std::sort(armiesVector.begin(), armiesVector.end());
	std::reverse(armiesVector.begin(), armiesVector.end());

	std::cout << "-------------------" << std::endl;

	for (i = 0; i < N; ++i)
		std::cout << armiesVector[i].Size() << std::endl;

	//Permet de maintenir la console lors d'un Run (sinon elle se ferme toute seul -__-')
	
	int xxxxxx;

	std::cin >> xxxxxx;
	std::cin.get();

	return 0;
}

