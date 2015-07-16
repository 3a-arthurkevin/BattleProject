#pragma once

#include "Point.h"

class Rectangle
{
	private:
		Point _topleft;
		float _width;
		float _height;

	public:
		Rectangle();

		Rectangle(const Point & topleft, float width, float height)
			: _topleft(topleft), _width(width), _height(height) {}

		Rectangle(const Rectangle & rectangle)
		{
			_topleft = rectangle._topleft;
			_width = rectangle._width;
			_height = rectangle._height;
		}

		void add(const Point& point)
		{
			_topleft += point;
		}
		void scale(const float scale)
		{
			_topleft *= scale;
			_width *= scale;
			_height *= scale;
		}

		bool include(const Point & point) const
		{
			bool conditionOne = (point.getX() >= _topleft.getX());
			bool conditionTwo = (point.getX() <= (_topleft.getX() + this->_width));
			bool conditionThree = (point.getY() <= _topleft.getY());
			bool conditionFour = (point.getY() >= (_topleft.getY() - this->_height));

			if ((conditionOne && conditionTwo) && (conditionThree && conditionFour))
				return true;
			else
				return false;
		}

		float area() const
		{
			return (_width * _height);
		}
		float perimeter() const
		{
			return (2 * (_width + _height));
		}
		Point center() const
		{
			Point p(_width / 2, _height / 2);
			return (p += (_topleft));
		}

		void setTopleft(const Point& topleft)
		{
			_topleft = topleft;
		}
		void setWidth(float width)
		{
			_width = width;
		}
		void setHeight(float height)
		{
			_height = height;
		}

		Point getTopleft() const
		{
			return _topleft;
		}
		float getWidth() const
		{
			return _width;
		}
		float getHeight() const
		{
			return _height;
		}
};

std::ostream & operator << (std::ostream & out, const Rectangle & p_rectangle);

