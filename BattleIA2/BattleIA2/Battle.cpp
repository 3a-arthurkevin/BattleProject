#include "Battle.h"

#include "AI.h"
#include "Action.h"

#include "SDL.h"
#include "SDL_image.h"

#undef main

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
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface *window = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("ESGI | BattleIA2", 0);
	SDL_Event event;
	SDL_Surface *unit_image = IMG_Load("Assets/images/unit.png");
	SDL_Surface *unit_image2 = IMG_Load("Assets/images/unit2.png");

	if (log)
	{
		std::cout << "-------------------------------" << std::endl;
		std::cout << "FIGHT" << std::endl;
		std::cout << "-------------------------------" << std::endl;
	}

	Army A = a;
	Army B = b;
	AI ai;
	int turn = 0;
	while (A.size()>0 && B.size()>0 && ++turn <= /*10000*/100) 
	{
		SDL_FillRect(window, &window->clip_rect, SDL_MapRGB(window->format, 0, 0, 0));
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) { exit(0); }
		if (event.key.keysym.sym == SDLK_ESCAPE) { exit(0); }

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
				action->execute(*(it->army), *(it->opponents), arena, log);
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

		for (auto punit : A.getUnitsList())
		{
			const Unit *unit = punit.get();
			
			SDL_Rect src = { 0, 0, unit_image->w, unit_image->h };
			SDL_Rect dst = { unit->getPosition().getX(), unit->getPosition().getY(), 8, 8 };

			SDL_BlitSurface(unit_image, &src, window, &dst);
		}

		for (auto punit : B.getUnitsList())
		{
			const Unit *unit = punit.get();

			SDL_Rect src = { 0, 0, unit_image2->w, unit_image2->h };
			SDL_Rect dst = { unit->getPosition().getX(), unit->getPosition().getY(), 8, 8 };

			SDL_BlitSurface(unit_image2, &src, window, &dst);
		}

		SDL_Flip(window);
	}

	SDL_FreeSurface(unit_image);
	SDL_FreeSurface(unit_image2);
	SDL_FreeSurface(window);
	SDL_Quit();

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
