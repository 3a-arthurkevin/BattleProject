#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <atomic>

#include "Capacity.h"

#include "Speed.h"
#include "LifePoint.h"
#include "Armor.h"
#include "Regen.h"
#include "WeaponDamage.h"
#include "WeaponRange.h"
#include "WeaponSpeed.h"

#include "Point.h"

class AI;

static std::atomic<int> idCounter = -1;

class Unit
{
	private:
		int _id;

		std::string _aiCode;

		Point _position;

		int _levelMaxCap;
		
		Speed _speed;
		LifePoint _lifePoint;
		Armor _armor;
		Regen _regen;
		WeaponDamage _weaponDamage;
		WeaponRange _weaponRange;
		WeaponSpeed _weaponSpeed;
		
	public:
		~Unit(void);

		Unit(int globalLevel);
		Unit(const std::string & IaCode, int speedLevel, int lifePointLevel, int armorLevel, int regenLevel, int weaponDamageLevel, int weaponRangeLevel, int weaponSpeedLevel);

		const int GetId() const;
		
		Speed & GetSpeed();
		LifePoint & GetLifePoint();
		Armor & GetArmor();
		Regen & GetRegen();
		WeaponDamage & GetWeaponDamage();
		WeaponRange & GetWeaponRange();
		WeaponSpeed & GetWeaponSpeed();
		
		Capacity & operator [](unsigned int value);

		int GetLevel();

		const Point & GetPosition() const;

		const std::string & GetAiCode() const;

		int GetLevelMaxCap() const;



		void Refresh();

		void SetPosition(const Point & point);

		const bool Shoot();

		void TakeDamage(float value);

		bool IsAlive() const;

		bool CanShoot() const;


		void Mutate();

		const int findCapacityNotCaped();

		const int findCapacityNotCaped(int index);

		Unit operator*(Unit & unit);
};

#endif
