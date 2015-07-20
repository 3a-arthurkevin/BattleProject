#pragma once

#ifndef BATTLE_H
#define BATTLE_H

#include <vector>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <iostream>

#include "Army.h"
#include "Rectangle.h"

//Run a fight between the two given armies, and store their score in the given variable.
void fight(const Rectangle& arena, const Army& a, const Army& b, int& scoreA, int& scoreB, bool log = false);

#endif //BATTLE_H