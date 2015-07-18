#pragma once

#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include "Army.h"
#include "Unit.h"

template <typename RETURN_TYPE>
class Extractor
{
	public:
		virtual RETURN_TYPE get(Unit& u, Army& a, Army& o) = 0;
};

#endif //EXTRACTOR_H
