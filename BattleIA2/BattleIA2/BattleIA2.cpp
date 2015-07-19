// BattleIA2.cpp : définit le point d'entrée pour l'application console.
//

#include <cstdlib>
#include <time.h>
#include <iostream>
#include "fstream"

#include "Army.h"
#include "Training.h"
#include "Rectangle.h"

#include "Extractor.h"
#include "ExtractorValue.h"
#include "ExtractorUnit.h"
#include "ExtractorPoint.h"
#include "ExtractorArmy.h"

#include "AiCodeGenerator.h"
#include "DecisionNode.h"

int main(void)
{
	std::srand(static_cast<unsigned int>(time(NULL)));

	std::shared_ptr<Army> champions;

	int iteration = 10;
	int threshold = 20;
	int populationSize = 3;
	int armySize = 10;
	int unitLevel = 10;

	if ( (threshold >= ((populationSize - 1) * armySize)) || threshold <= 0 )
		threshold = ((populationSize - 1) * armySize) / 2;

	std::string const fileName = "Army_" + std::to_string(armySize) + "_" + std::to_string(unitLevel) + ".save";

	try
	{
		std::ifstream in(fileName);
		Army army = Army::load(in);
		std::cout << army << std::endl;
		champions = std::shared_ptr<Army>(new Army(army));
	}
	catch (...)
	{
		std::cout << "Erreur lors du chargement du fichier" << std::endl;
		champions = nullptr;
	} 

	float arenaSize = (populationSize) * 10.f;
	Rectangle arena(Point(0.00f, arenaSize), arenaSize, arenaSize);

	std::unique_ptr<Army> army = train(arena, iteration, threshold, populationSize, armySize, unitLevel, champions);
	std::cout << *army << std::endl;

	std::ofstream out(fileName);
	army->save(out);
	out.flush();
	out.close();

	std::cin.ignore();
	return 0;
}

