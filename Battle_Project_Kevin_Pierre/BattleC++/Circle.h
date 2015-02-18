#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"

const float M_PI = 3.14159265358979323846f;

class Circle
{
	private:
		Point _center;
		float _radius;

	public:
		~Circle();

		Circle();
		Circle(const Point & point, float radius);
		Circle(const Circle & circle);

		void Add(const Point & point);
		void Scale(float scale);

		bool Include(const Point & point) const;
		bool Intersect(const Circle & circle) const;

		float Area() const;
		float Perimeter() const;
		Point Center() const;

		void SetCenter(const Point & center);
		void SetRadius(float radius);

		Point GetCenter() const;
		float GetRadius() const;

		Circle & operator+=(const Point & point);
		Circle operator+(const Point & point) const;

		Circle & operator-=(const Point & point);
		Circle operator-(const Point & point);

		Circle & operator*=(float value);
		Circle operator*(float value) const;

		Circle & operator/=(float value);
		Circle operator/(float value) const;
};

std::ostream & operator << (std::ostream & out, const Circle & p_circle);

#endif // CIRCLE_H