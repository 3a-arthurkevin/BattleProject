#pragma once

#include "capacity.h"

#include "Speed.h"
#include "LifePoint.h"
#include "Armor.h"
#include "Regen.h"
#include "Damage.h"
#include "WeaponRange.h"
#include "WeaponSpeed.h"

#include <string>

#include "Point.h"

class Unit
{
	private:
		int _id;

		Point _position;

		Speed _speed;
		LifePoint _lifePoint;
		Armor _armor;
		Regen _regen;
		Damage _damage;
		WeaponRange _weaponRange;
		WeaponSpeed _WeaponSpeed;

	public:
		~Unit(void);

		Unit(int globalLevel);
		Unit(std::string IaCode, int speedLevel, int lifePointLevel, int armorLevel, int regenLevel, int damageLevel, int weaponRangeLevel, int weaponSpeedLevel);

		const int GetId() const;
		void SetId(int id);

		Speed & GetSpeed();
		LifePoint & GetLifePoint();
		Armor & GetArmor();
		Regen & getRegen();
		Damage & getDamage();
		WeaponRange & getWeaponRange();
		WeaponSpeed & getWeaponSpeed();

		float operator [](unsigned int value);

		const int GetLevel() const;

		const Point & GetPosition() const;

		void Refresh();

		void SetPosition(int x, int y);

		const bool Shoot();

		void GetDamage(float value);

		const bool IsAlive() const;
};

