#include "Battle.h"

#include "AI.h"
#include "Action.h"

//Struct used to manipulate a unit together with its army and its opponents
struct UnitChoice
{
	Army* army;
	Army* opponents;
	int unitId;
	UnitChoice(int id, Army* a, Army* o) :unitId(id), army(a), opponents(o) {}
};


//Return a position according to the arena's size in order to set all units position before the war
Point getRandomPosition(const Rectangle& arena)
{
	float x = static_cast<float>(rand() % (static_cast<int>(arena.getWidth() /*+ arena.getTopleft().getX()*/)));
	float y = static_cast<float>(rand() % (static_cast<int>(arena.getHeight() /*+ arena.getTopleft().getY()*/)));

	return Point(x, y);
}

//Run a fight between the two given armies, and store their score in the given variable.
void fight(const Rectangle& arena, const Army& a, const Army& b, int& scoreA, int& scoreB, bool log)
{
	if (log)
	{
		std::cout << "-------------------------------" << std::endl;
		std::cout << "FIGHT" << std::endl;
		std::cout << "-------------------------------" << std::endl;
	}

	Army A = a;
	Army B = b;

	for (int i = 0; i < A.size(); ++i)
	{
		A.getUnitsList()[i]->setPosition(getRandomPosition(arena));
	}
	for (int i = 0; i < B.size(); ++i)
	{
		B.getUnitsList()[i]->setPosition(getRandomPosition(arena));
	}

	AI ai;
	int turn = 0;
	while (A.size()>0 && B.size()>0 && ++turn <= /*10000*/100) 
	{
		if (log)
		{
			std::cout << "-------------------------------" << std::endl;
			std::cout << "Turn " << (turn) << std::endl;
			std::cout << "-------------------------------" << std::endl;
		}

		std::vector<UnitChoice> order;
		std::transform(A.getUnitsList().begin(), A.getUnitsList().end(), std::back_inserter(order),
			[&A, &B](std::shared_ptr<Unit>& u)
		{
			u->refresh();
			return UnitChoice(u->getId(), &A, &B);
		});
		std::transform(B.getUnitsList().begin(), B.getUnitsList().end(), std::back_inserter(order),
			[&A, &B](std::shared_ptr<Unit>& u)
		{
			u->refresh();
			return UnitChoice(u->getId(), &B, &A);
		});
		std::random_shuffle(order.begin(), order.end());

		for (auto it = order.begin(); it != order.end(); it++)
		{
			try
			{
				if (log)std::cout << "Unit#" << it->unitId << " (Army " << ((it->army) == &A ? "A" : "B") << ") : ";
				Unit& unit = it->army->getUnit(it->unitId);
				std::unique_ptr<Action> action = ai(unit, *(it->army), *(it->opponents), arena);
				action->execute(log);
				it->opponents->purge();
				std::cout << std::endl;
			}
			catch (std::invalid_argument e)
			{
				//can happens if the unit is already dead or if an army is empty
				std::cout << std::endl;
				std::cout << "Catch - Battle.cpp" << std::endl;
				std::cout << std::endl;
				continue;
			}
		}

	}

	if (log)
	{
		if (A.size() == 0)
		{
			std::cout << "Army B win " << B.size() << " to 0" << std::endl;
		}
		else if (B.size() == 0)
		{
			std::cout << "Army A win " << A.size() << " to 0" << std::endl;
		}
		else
		{
			std::cout << "No army defeated after 100 turns" << std::endl;
			std::cout << "Army A score : " << A.size() << "  |  Army B score : " << B.size() << std::endl;
		}
	}

	scoreA = A.size() - B.size();
	scoreB = B.size() - A.size();

	if (scoreA < 0)
		scoreA = 0;
	if (scoreB < 0)
		scoreB = 0;

	if (log)
	{
		std::cout << "-------------------------------" << std::endl;
		std::cout << "END FIGHT" << std::endl;
		std::cout << "-------------------------------" << std::endl;
	}
}
