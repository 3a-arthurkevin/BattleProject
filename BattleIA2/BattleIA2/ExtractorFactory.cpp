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
			case '[':
			{
				float value = 0.f;
				aiCode >> value;
				aiCode >> c;
				return std::unique_ptr < Extractor<float> >
					(new ExtractorValue(value));
			}
			case 'C':
			{
				int indexCapacity;
				aiCode >> indexCapacity;
				if (indexCapacity >= 0 && indexCapacity <= 6)
					return std::unique_ptr < Extractor<float> >
						(new ExtractorCxUnitValue(getUnitExtractor(aiCode), indexCapacity));

				break;
			}
			case 'D':
			{
				return std::unique_ptr < Extractor<float> >
					(new ExtractorDistanceUnitPointValue(getUnitExtractor(aiCode), getPointExtractor(aiCode)));
			}
			case 'M':
			{
				aiCode >> c;
				if (c == 'D')
					return std::unique_ptr < Extractor<float> >
						(new ExtractorMaxDistancePointArmyValue(getArmyExtractor(aiCode), getPointExtractor(aiCode)));

				int indexCapacity = c - '0';
				if (indexCapacity >= 0 && indexCapacity <= 6)
					return std::unique_ptr < Extractor<float> >
						(new ExtractorMaxCxArmyValue(getArmyExtractor(aiCode), indexCapacity));

				break;
			}
			case 'm':
			{
				aiCode >> c;
				if (c == 'D')
					return std::unique_ptr < Extractor<float> >
						(new ExtractorMinDistancePointArmyValue(getArmyExtractor(aiCode), getPointExtractor(aiCode)));
				
				int indexCapacity = c - '0';
				if (indexCapacity >= 0 && indexCapacity <= 6)
					return std::unique_ptr < Extractor<float> >
						(new ExtractorMinCxArmyValue(getArmyExtractor(aiCode), indexCapacity));
					
				break;
			}

			case 'a':
			{
				aiCode >> c;
				if (c == 'D')
					return std::unique_ptr < Extractor<float> >
						(new ExtractorAvgDistancePointArmyValue(getArmyExtractor(aiCode), getPointExtractor(aiCode)));

				int indexCapacity = c - '0';
				if (indexCapacity >= 0 && indexCapacity <= 6)
					return std::unique_ptr < Extractor<float> >
						(new ExtractorAvgCxArmyValue(getArmyExtractor(aiCode), indexCapacity));

				break;
			}
		}

		return std::unique_ptr < Extractor<float> >
			(new ExtractorValue(-1.f));
	}
	catch (...)
	{
		std::cout << "Erreur dans la Factory Extractor Value" << std::endl;
		return std::unique_ptr < Extractor<float> >
					(new ExtractorValue(-1.f));
	}
}

std::unique_ptr<Extractor<Unit>>ExtractorFactory:: getUnitExtractor(std::stringstream& aiCode)
{
	aiCode.exceptions(std::stringstream::eofbit | std::stringstream::failbit | std::stringstream::badbit);
	try
	{
		char c;
		aiCode >> c;
		switch (c)
		{
			case 'U':
			{
				return std::unique_ptr < Extractor<Unit> >
					(new ExtractorUnit());
			}
			case 'L':
			{
				aiCode >> c;
				if (c == 'D')
					return std::unique_ptr < Extractor<Unit> >
						(new ExtractorMinDistancePointArmyUnit(getArmyExtractor(aiCode), getPointExtractor(aiCode)));

				int indexCapacity = c - '0';
				if (indexCapacity >= 0 && indexCapacity <= 6)
					return std::unique_ptr < Extractor<Unit> >
						(new ExtractorMinCxArmyUnit(getArmyExtractor(aiCode), indexCapacity));

				break;
			}

			case 'H':
			{
				aiCode >> c;

				if (c == 'D')
					return std::unique_ptr < Extractor<Unit> >
						(new ExtractorMaxDistancePointArmyUnit(getArmyExtractor(aiCode), getPointExtractor(aiCode)));

				int indexCapacity = c - '0';
				if (indexCapacity >= 0 && indexCapacity <= 6)
					return std::unique_ptr < Extractor<Unit> >
						(new ExtractorMaxCxArmyUnit(getArmyExtractor(aiCode), indexCapacity));

				break;
			}
		}

		return std::unique_ptr < Extractor<Unit> >
			(new ExtractorUnit());
	}
	catch (...)
	{
		std::cout << "Erreur dans la Factory Extractor Unit" << std::endl;
		return std::unique_ptr < Extractor<Unit> >
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
			case 'B':
			{
				return std::unique_ptr < Extractor<Point> >
					(new ExtractorCentroidArmyPoint(getArmyExtractor(aiCode)));
			}
			case 'P':
			{
				return std::unique_ptr < Extractor<Point> >
					(new ExtractorPointUnitPoint(getUnitExtractor(aiCode)));
			}
			default:
			{
				return std::unique_ptr < Extractor<Point> >
					(new ExtractorCentroidArmyPoint(getArmyExtractor(aiCode)));
			}
		}
	}
	catch (...)
	{
		std::cout << "Erreur dans la Factory Extractor Point" << std::endl;
		return std::unique_ptr < Extractor<Point> >
			(new ExtractorCentroidArmyPoint(getArmyExtractor(aiCode)));
	}
}

std::unique_ptr<Extractor<Army>> ExtractorFactory::getArmyExtractor(std::stringstream& aiCode)
{
	aiCode.exceptions(std::stringstream::eofbit | std::stringstream::failbit | std::stringstream::badbit);
	try
	{
		char c;
		aiCode >> c;
		if(c ==  'A')
		{
			return std::unique_ptr < Extractor<Army> >
				(new ExtractorArmyA());
		}
		else if (c == 'O')
		{
			return std::unique_ptr < Extractor<Army> >
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
					return std::unique_ptr < Extractor<Army>>
						(new ExtractorTCxSmallerValueSetArmy(indexCapacity, getValueExtractor(aiCode), getArmyExtractor(aiCode)));
				}
			}
			else if (c == 'H')
			{
				aiCode >> c;
				int indexCapacity = c - '0';
				if (indexCapacity >= 0 && indexCapacity <= 6)
				{
					return std::unique_ptr < Extractor<Army>>
						(new ExtractorTCxGreaterValueSetArmy(indexCapacity, getValueExtractor(aiCode), getArmyExtractor(aiCode)));
				}
			}

			return std::unique_ptr < Extractor<Army> >
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
					return std::unique_ptr < Extractor<Army> >
						(new ExtractorNMinDistancePointSetArmy(nbElement, getPointExtractor(aiCode), getArmyExtractor(aiCode)));
				}

				int indexCapacity = c - '0';
				if (c >= 0 && c <= 6)
				{
					return std::unique_ptr < Extractor<Army> >
						(new ExtractorNMinCxSetArmy(nbElement, indexCapacity, getArmyExtractor(aiCode)));
				}
			}
			else if (c == 'H')
			{
				aiCode >> c;
				if (c == 'D')
				{
					return std::unique_ptr < Extractor<Army> >
						(new ExtractorNMaxDistancePointSetArmy(nbElement, getPointExtractor(aiCode), getArmyExtractor(aiCode)));
				}

				int indexCapacity = c - '0';
				if (c >= 0 && c <= 6)
				{
					return std::unique_ptr < Extractor<Army> >
						(new ExtractorNMaxCxSetArmy(nbElement, indexCapacity, getArmyExtractor(aiCode)));
				}
			}
		}

		return std::unique_ptr < Extractor<Army> >
			(new ExtractorArmyO());
	}
	catch (...)
	{
		std::cout << "Erreur dans la Factory Extractor Army" << std::endl;
		return std::unique_ptr < Extractor<Army> >
			(new ExtractorArmyO());
	}
}