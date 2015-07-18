#pragma once

#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include "Army.h"
//#include "AiFactory.h"

template <typename returnType>
class Extractor
{
	public:
		virtual returnType get(Unit& u, Army& a, Army& o) = 0;
};

#endif //EXTRACTOR_H
