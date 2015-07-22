#include "ExtractorFactory.h"

#include "ExtractorValue.h"
#include "ExtractorUnit.h"
#include "ExtractorArmy.h"
#include "ExtractorPoint.h"

//Read AiCode to return the right Value Extractor
std::unique_ptr<Extractor<float>> ExtractorFactory::getValueExtractor(std::stringstream& aiCode)
{
	aiCode.exceptions(std::stringstream::eofbit | std::stringstream::failbit | std::stringstream::badbit);
	try
	{
		char c;
		aiCode >> c;
		switch (c)
		{
			//Case [val]
			case '[':
			{
				float value = 0.f;
				aiCode >> value;
				aiCode >> c;
				return std::unique_ptr < Extractor<float> >
					(new ExtractorValue(value));
			}
			//Case C0-C6<Unit>
			case 'C':
			{
				int indexCapacity;
				aiCode >> indexCapacity;

				if (indexCapacity >= 0 && indexCapacity <= 6)
				{
					std::unique_ptr<Extractor<Unit&>> exUnit = std::unique_ptr<Extractor<Unit&>> (getUnitExtractor(aiCode));

					return std::unique_ptr < Extractor<float> >
						(new ExtractorCxUnitValue(exUnit, indexCapacity));
				}

				break;
			}
			//Case D<Unit><Point>
			case 'D':
			{
				std::unique_ptr<Extractor<Unit&>> exUnit = std::unique_ptr<Extractor<Unit&>>(getUnitExtractor(aiCode));
				std::unique_ptr<Extractor<Point>> exPoint = std::unique_ptr<Extractor<Point>>(getPointExtractor(aiCode));

				return std::unique_ptr < Extractor<float> >
					(new ExtractorDistanceUnitPointValue(exUnit, exPoint));
			}
			//Case M/m/aD<Set><Point>
			//Case M/m/a0-6<Set>
			case 'M':
			{
				aiCode >> c;
				if (c == 'D')
				{
					std::unique_ptr<Extractor<SetUnit>> exArmy = std::unique_ptr<Extractor<SetUnit>>(getArmyExtractor(aiCode));
					std::unique_ptr<Extractor<Point>> exPoint = std::unique_ptr<Extractor<Point>>(getPointExtractor(aiCode));

					return std::unique_ptr < Extractor<float> >
						(new ExtractorMaxDistancePointArmyValue(exArmy, exPoint));
				}

				int indexCapacity = c - '0';
				if (indexCapacity >= 0 && indexCapacity <= 6)
				{
					std::unique_ptr<Extractor<SetUnit>> exArmy = std::unique_ptr<Extractor<SetUnit>>(getArmyExtractor(aiCode));

					return std::unique_ptr < Extractor<float> >
						(new ExtractorMaxCxArmyValue(exArmy, indexCapacity));
				}

				break;
			}
			case 'm':
			{
				aiCode >> c;
				if (c == 'D')
				{
					std::unique_ptr<Extractor<SetUnit>> exArmy = std::unique_ptr<Extractor<SetUnit>>(getArmyExtractor(aiCode));
					std::unique_ptr<Extractor<Point>> exPoint = std::unique_ptr<Extractor<Point>>(getPointExtractor(aiCode));

					return std::unique_ptr < Extractor<float> >
						(new ExtractorMinDistancePointArmyValue(exArmy, exPoint));
				}
				
				int indexCapacity = c - '0';
				if (indexCapacity >= 0 && indexCapacity <= 6)
				{
					std::unique_ptr<Extractor<SetUnit>> exArmy = std::unique_ptr<Extractor<SetUnit>>(getArmyExtractor(aiCode));

					return std::unique_ptr < Extractor<float> >
						(new ExtractorMinCxArmyValue(exArmy, indexCapacity));
				}
					
				break;
			}

			case 'a':
			{
				aiCode >> c;
				if (c == 'D')
				{
					std::unique_ptr<Extractor<SetUnit>> exArmy = std::unique_ptr<Extractor<SetUnit>>(getArmyExtractor(aiCode));
					std::unique_ptr<Extractor<Point>> exPoint = std::unique_ptr<Extractor<Point>>(getPointExtractor(aiCode));

					return std::unique_ptr < Extractor<float> >
						(new ExtractorAvgDistancePointArmyValue(exArmy, exPoint));
				}

				int indexCapacity = c - '0';
				if (indexCapacity >= 0 && indexCapacity <= 6)
				{
					std::unique_ptr<Extractor<SetUnit>> exArmy = std::unique_ptr<Extractor<SetUnit>>(getArmyExtractor(aiCode));

					return std::unique_ptr < Extractor<float> >
						(new ExtractorAvgCxArmyValue(exArmy, indexCapacity));
				}

				break;
			}
		}

		std::cout << "1 - Erreur dans la Factory Extractor Value" << std::endl;
		return std::unique_ptr < Extractor<float> >
			(new ExtractorValue(-1.f));
	}
	catch (...)
	{
		std::cout << "2 - Erreur dans la Factory Extractor Value" << std::endl;
		return std::unique_ptr < Extractor<float> >
					(new ExtractorValue(-1.f));
	}
}

std::unique_ptr<Extractor<Unit&>> ExtractorFactory::getUnitExtractor(std::stringstream& aiCode)
{
	aiCode.exceptions(std::stringstream::eofbit | std::stringstream::failbit | std::stringstream::badbit);
	try
	{
		char c;
		aiCode >> c;
		switch (c)
		{
			//Case U
			case 'U':
			{
				return std::unique_ptr < Extractor<Unit&> >
					(new ExtractorUnit());
			}
			//Case LD<Set><Point> | HD<Set><Point>
			//Case L0-6<Set> | H0-6<Set>
			case 'L':
			{
				aiCode >> c;
				if (c == 'D')
				{
					std::unique_ptr<Extractor<SetUnit>> exArmy = std::unique_ptr<Extractor<SetUnit>>(getArmyExtractor(aiCode));
					std::unique_ptr<Extractor<Point>> exPoint = std::unique_ptr<Extractor<Point>>(getPointExtractor(aiCode));

					return std::unique_ptr < Extractor<Unit&> >
						(new ExtractorMinDistancePointArmyUnit(exArmy, exPoint));
				}

				int indexCapacity = c - '0';
				if (indexCapacity >= 0 && indexCapacity <= 6)
				{
					std::unique_ptr<Extractor<SetUnit>> exArmy = std::unique_ptr<Extractor<SetUnit>>(getArmyExtractor(aiCode));

					return std::unique_ptr < Extractor<Unit&> >
						(new ExtractorMinCxArmyUnit(exArmy, indexCapacity));
				}

				break;
			}

			case 'H':
			{
				aiCode >> c;

				if (c == 'D')
				{
					std::unique_ptr<Extractor<SetUnit>> exArmy = std::unique_ptr<Extractor<SetUnit>>(getArmyExtractor(aiCode));
					std::unique_ptr<Extractor<Point>> exPoint = std::unique_ptr<Extractor<Point>>(getPointExtractor(aiCode));

					return std::unique_ptr < Extractor<Unit&> >
						(new ExtractorMaxDistancePointArmyUnit(exArmy, exPoint));
				}

				int indexCapacity = c - '0';
				if (indexCapacity >= 0 && indexCapacity <= 6)
				{
					std::unique_ptr<Extractor<SetUnit>> exArmy = std::unique_ptr<Extractor<SetUnit>>(getArmyExtractor(aiCode));

					return std::unique_ptr < Extractor<Unit&> >
						(new ExtractorMaxCxArmyUnit(exArmy, indexCapacity));
				}

				break;
			}
		}

		std::cout << "1 - Erreur dans la Factory Extractor Unit" << std::endl;
		return std::unique_ptr < Extractor<Unit&> >
			(new ExtractorUnit());
	}
	catch (...)
	{
		std::cout << "2 - Erreur dans la Factory Extractor Unit" << std::endl;
		return std::unique_ptr < Extractor<Unit&> >
			(new ExtractorUnit());
	}
}

std::unique_ptr<Extractor<Point>> ExtractorFactory::getPointExtractor(std::stringstream& aiCode)
{
	aiCode.exceptions(std::stringstream::eofbit | std::stringstream::failbit | std::stringstream::badbit);
	try
	{
		char c;
		aiCode >> c;
		switch (c)
		{
			//Case B<Set>
			case 'B':
			{
				std::unique_ptr<Extractor<SetUnit>> exArmy = std::unique_ptr<Extractor<SetUnit>>(getArmyExtractor(aiCode));

				return std::unique_ptr < Extractor<Point> >
					(new ExtractorCentroidArmyPoint(exArmy));
			}
			//Case P<Unit>
			case 'P':
			{
				std::unique_ptr<Extractor<Unit&>> exUnit = std::unique_ptr<Extractor<Unit&>>(getUnitExtractor(aiCode));

				return std::unique_ptr < Extractor<Point> >
					(new ExtractorPointUnitPoint(exUnit));
			}
			default:
			{
				std::cout << "1 - Erreur dans la Factory Extractor Point" << std::endl;
				std::unique_ptr<Extractor<Unit&>> exUnit = std::unique_ptr<Extractor<Unit&>>(getUnitExtractor(aiCode));

				return std::unique_ptr < Extractor<Point> >
					(new ExtractorPointUnitPoint(exUnit));
			}
		}
	}
	catch (...)
	{
		std::cout << "2 - Erreur dans la Factory Extractor Point" << std::endl;
		std::unique_ptr<Extractor<Unit&>> exUnit = std::unique_ptr<Extractor<Unit&>>(getUnitExtractor(aiCode));

		return std::unique_ptr < Extractor<Point> >
			(new ExtractorPointUnitPoint(exUnit));
	}
}

std::unique_ptr<Extractor<SetUnit>> ExtractorFactory::getArmyExtractor(std::stringstream& aiCode)
{
	aiCode.exceptions(std::stringstream::eofbit | std::stringstream::failbit | std::stringstream::badbit);
	try
	{
		char c;
		aiCode >> c;
		if(c ==  'A')
		{
			return std::unique_ptr < Extractor<SetUnit> >
				(new ExtractorArmyA());
		}
		else if (c == 'O')
		{
			return std::unique_ptr < Extractor<SetUnit> >
				(new ExtractorArmyO());
		}
		else if (c == 'T')
		{
			aiCode >> c;
			if (c == 'L')
			{
				aiCode >> c;
				int indexCapacity = c - '0';
				if (indexCapacity >= 0 && indexCapacity <= 6)
				{
					std::unique_ptr<Extractor<float>> exValue = std::unique_ptr<Extractor<float>>(getValueExtractor(aiCode));
					std::unique_ptr<Extractor<SetUnit>> exArmy = std::unique_ptr<Extractor<SetUnit>>(getArmyExtractor(aiCode));

					return std::unique_ptr < Extractor<SetUnit>>
						(new ExtractorTCxSmallerValueSetArmy(indexCapacity, exValue, exArmy));
				}
			}
			else if (c == 'H')
			{
				aiCode >> c;
				int indexCapacity = c - '0';
				if (indexCapacity >= 0 && indexCapacity <= 6)
				{
					std::unique_ptr<Extractor<float>> exValue = std::unique_ptr<Extractor<float>>(getValueExtractor(aiCode));
					std::unique_ptr<Extractor<SetUnit>> exArmy = std::unique_ptr<Extractor<SetUnit>>(getArmyExtractor(aiCode));

					return std::unique_ptr < Extractor<SetUnit>>
						(new ExtractorTCxGreaterValueSetArmy(indexCapacity, exValue, exArmy));
				}
			}

			return std::unique_ptr < Extractor<SetUnit> >
				(new ExtractorArmyO());
		}

		int nbElement = c - '0';
		if (nbElement >= 1 && nbElement <= 9)
		{
			aiCode >> c;
			if (c == 'L')
			{
				aiCode >> c;
				if (c == 'D')
				{
					std::unique_ptr<Extractor<Point>> exPoint = std::unique_ptr<Extractor<Point>>(getPointExtractor(aiCode));
					std::unique_ptr<Extractor<SetUnit>> exArmy = std::unique_ptr<Extractor<SetUnit>>(getArmyExtractor(aiCode));

					return std::unique_ptr < Extractor<SetUnit> >
						(new ExtractorNMinDistancePointSetArmy(nbElement, exPoint, exArmy));
				}

				int indexCapacity = c - '0';
				if (indexCapacity >= 0 && indexCapacity <= 6)
				{
					std::unique_ptr<Extractor<SetUnit>> exArmy = std::unique_ptr<Extractor<SetUnit>>(getArmyExtractor(aiCode));

					return std::unique_ptr < Extractor<SetUnit> >
						(new ExtractorNMinCxSetArmy(nbElement, indexCapacity, exArmy));
				}
			}
			else if (c == 'H')
			{
				aiCode >> c;
				if (c == 'D')
				{
					std::unique_ptr<Extractor<Point>> exPoint = std::unique_ptr<Extractor<Point>>(getPointExtractor(aiCode));
					std::unique_ptr<Extractor<SetUnit>> exArmy = std::unique_ptr<Extractor<SetUnit>>(getArmyExtractor(aiCode));

					return std::unique_ptr < Extractor<SetUnit> >
						(new ExtractorNMaxDistancePointSetArmy(nbElement, exPoint, exArmy));
				}

				int indexCapacity = c - '0';
				if (indexCapacity >= 0 && indexCapacity <= 6)
				{
					std::unique_ptr<Extractor<SetUnit>> exArmy = std::unique_ptr<Extractor<SetUnit>>(getArmyExtractor(aiCode));

					return std::unique_ptr < Extractor<SetUnit> >
						(new ExtractorNMaxCxSetArmy(nbElement, indexCapacity, exArmy));
				}
			}
		}

		return std::unique_ptr < Extractor<SetUnit> >
			(new ExtractorArmyO());
	}
	catch (...)
	{
		std::cout << "Erreur dans la Factory Extractor Army" << std::endl;
		return std::unique_ptr < Extractor<SetUnit> >
			(new ExtractorArmyO());
	}
}