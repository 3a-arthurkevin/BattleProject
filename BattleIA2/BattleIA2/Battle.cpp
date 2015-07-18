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
	AI ai;
	int turn = 1;
	while (A.size()>0 && B.size()>0 && turn++ < /*10000*/50) 
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
			}
			catch (std::invalid_argument e)
			{

				//can happens if the unit is already dead or if an army is empty
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
			std::cout << "No army defeated after 500 turns" << std::endl;
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
