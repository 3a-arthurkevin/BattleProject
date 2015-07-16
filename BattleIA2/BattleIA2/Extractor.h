#pragma once

#include "Army.h"

template <typename returnType>
class Extractor
{
	public:
		virtual returnType get(Unit& u, Army& a, Army& o) = 0;
};

