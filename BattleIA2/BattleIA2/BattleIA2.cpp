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
	/*
	std::srand(static_cast<unsigned int>(time(NULL)));
	std::shared_ptr<Army> champions;

	int iteration = 100;
	int threshold = 500;
	int populationSize = 10;
	int armySize = 5;
	int unitLevel = 10;

	if ( (threshold >= ((populationSize - 1) * armySize)) || threshold <= 0 )
		threshold = ((populationSize - 1) * armySize) / 2;

	std::string const fileName = "Army_" + std::to_string(armySize) + "_" + std::to_string(unitLevel) + ".save";

	try
	{
		//std::ifstream in("Army_10_100.save");
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

	float arenaSize = (populationSize + (unitLevel/2.f)) * 10.f;

	Rectangle arena(Point(0.00f, arenaSize), arenaSize, arenaSize);

	//std::unique_ptr<Army> army = train(100, 1000, 100, 10, 100, champions);
	std::unique_ptr<Army> army = train(arena, iteration, threshold, populationSize, armySize, unitLevel, champions);
	std::cout << *army << std::endl;
	//std::ofstream out("Army_10_100.save");
	std::ofstream out(fileName);
	army->save(out);
	out.flush();
	out.close();
	*/

	
	Army a = Army(5, 10);
	Army o = Army(5, 10);
	Unit u = *(a.getUnitsList()[0]);

	/*
	std::unique_ptr<Extractor<float>>ex = std::unique_ptr<Extractor<float>>(new ExtractorValue(5));

	std::cout << ex->get(*u, a, o) << std::endl;
	*/

	std::string test = AiCodeGenerator::generateAiCode();
	std::stringstream code;
	code << test;
	DecisionNode dn = DecisionNode(code);
	std::unique_ptr<Action> action = dn.get(u, a, o);
	std::cin.ignore();

	return 0;
}

