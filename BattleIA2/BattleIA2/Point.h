#pragma once

#include <cmath>
#include <ostream>
#include <iomanip>

//Class representing a position with a point
class Point
{
	private:
		float _x;//X coordinate
		float _y;//Y coordinate

	public:
		//Natural constructor
		Point(float x = 0.0f, float y = 0.0f) :_x(x), _y(y) {}


		////////////////////////
		//getters
		////////////////////////
		float getX()const
		{
			return _x;
		}

		float getY()const
		{
			return _y;
		}

		///////////////////////
		//setters
		///////////////////////
		void setX(float x)
		{
			_x = x;
		}

		void setY(float y)
		{
			_y = y;
		}

		/////////////////////////////////////
		//arithmetic operators overloading
		/////////////////////////////////////

		//Base operator
		Point& operator+=(const Point& p)
		{
			_x += p._x;
			_y += p._y;
			return (*this);
		}

		Point& operator-=(const Point& p)
		{
			_x -= p._x;
			_y -= p._y;
			return (*this);
		}

		Point& operator*=(float s)
		{
			_x *= s;
			_y *= s;
			return (*this);
		}

		//Derived operator from base operator
		Point& operator/=(float s)
		{
			return (*this *= (1.0f / s));
		}

		Point operator+(Point p)const
		{
			return (Point(*this) += p);
		}

		Point operator-(const Point& p)const
		{
			return (Point(*this) -= p);
		}

		Point operator*(float s)const
		{
			return (Point(*this) *= s);
		}

		Point operator/(float s)const
		{
			return (Point(*this) /= s);
		}

		Point operator-()const
		{
			return Point(-_x, -_y);
		}

		//Compute the dot product with another point
		float dot(const Point& p)const
		{
			return ( ((_x * p._x)) + ((_y * p._y)) );
		}

		//Compute the norm of the point
		float norm()const
		{
			return sqrt(this->dot(*this));
		}

		//Compute the Euclidian distance between this point and another
		float distance(Point p)const
		{
			p -= *this;
			return p.norm();
		}

		//Translate this point in direction of the one in parameter:
		// if distance is bigger than max, translate to max units
		// otherwise translate to the position p
		void moveTo(const Point& p, float max)
		{
			Point vec = (p - (*this));
			float d = vec.norm();
			if (d <= max) 
				(*this) += vec;
			else 
				(*this) += (vec*(max / d));
		}
};

//Star operator overloading. Case  Scalar*Point
inline Point operator*(float s, Point p)
{
	return (p *= s);
}

//Shift operator overloading, printing the point in the output stream.
inline std::ostream& operator<<(std::ostream& out, const Point& p)
{
	out << std::fixed << std::setprecision(1) << "(" << p.getX() << "," << p.getY() << ")";
	return out;
}
