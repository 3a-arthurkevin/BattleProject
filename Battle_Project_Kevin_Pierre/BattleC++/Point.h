#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>

class Point
{
	private:
		float _x;
		float _y;

    public:
		~Point(void);

        Point(void);
        Point(float x, float y);
        Point(const Point & point);

        void Add(const Point & point);

        void Scale(float scale);

        void SetX(float x);
        void SetY(float y);

        float GetX() const;
        float GetY() const;

        float Distance(const Point & point) const;

        Point & operator+=(const Point & point);
        Point operator+(const Point & point) const;

        Point operator-() const;
        Point & operator-=(const Point & point);
        Point operator-(const Point & point);

        Point & operator*=(float value);
        Point operator*(float value) const;

        Point & operator/=(float value);
        Point operator/(float value) const;
};

std::ostream & operator << (std::ostream & out, const Point & point);

#endif // POINT_H