#pragma once

class Capacity
{
	protected:
		//Level of the capacity
		int _level;
		//Value of the capacity
		float _value;

		//Method updating the value of the capacity in regard of the level
		virtual void updateValue() = 0;

	public:
		//Constructor takes level as parameter
		Capacity(int level) :_level(level) {}

		//Destructor
		virtual ~Capacity() {}

		//Increase the level of the capacity
		void upgrade(int nbLevelToAdd = 1)
		{
			_level += nbLevelToAdd;
			updateValue();
		}

		//Decrease the level of the capacity
		void downgrade(int nbLevelToRemove = 1)
		{
			_level -= nbLevelToRemove;
			if (_level < 0) _level = 0;
			updateValue();
		}

		//Level getter
		int getLevel() const
		{
			return _level;
		}

		//Value getter
		float getValue() const
		{
			return _value;
		}
};

