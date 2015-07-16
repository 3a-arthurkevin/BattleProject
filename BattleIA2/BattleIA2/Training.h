#pragma once

#include <memory>
#include <vector>
#include <iterator>

#include "Army.h"

#include "Battle.h"


/*
	Return a random position
	Used to set units position before the war begin
*/
Point getRandomPosition(const Rectangle& arena);



//Train armies by genetic algorithm,  with fitness function obtained by tournament
//params :
// - iterations : the maximum number of iterations of the genetic algorithm
// - threshold : the score to reach for an army to be considered as winner
// - populationSize : number of armies in one iteration
// - armySize : number of units per army
// - unitLevel : global level of each unit in each army
// - champions : optionnal armies which have to be defeated
std::unique_ptr<Army> train(const Rectangle& arena, int iterations, int threshold, int populationSize, int armySize, int unitLevel, std::shared_ptr<Army>& champions);


