#include "Point.h"

Point::~Point()
{

}

Point::Point()
{
    this->_x = 0.f;
    this->_y = 0.f;
}

Point::Point(float x, float y)
{
    this->_x = x;
    this->_y = y;
}

Point::Point(const Point & point)
{
    this->_x = point._x;
    this->_y = point._y;
}

void Point::Add(const Point & point)
{
    this->_x += point._x;
    this->_y += point._y;
}

void Point::Scale(float scale)
{
    this->_x *= scale;
    this->_y *= scale;
}

void Point::SetX(float x)
{
    this->_x = x;
}

void Point::SetY(float y)
{
    this->_y = y;
}

float Point::GetX() const
{
    return this->_x;
}

float Point::GetY() const
{
    return this->_y;
}

float Point::Distance(const Point & point) const
{
    return sqrt(((this->_x - point._x)*(this->_x - point._x)) + ((this->_y - point._y)*(this->_y - point._y)));
}

Point & Point::operator+=(const Point & point)
{
    this->Add(point);
    return *this;
}

Point Point::operator+(const Point & point) const
{
    Point p(*this);
    p += point;
    return p;
}

Point Point::operator-() const
{
    return Point(-this->_x, -this->_y);
}

Point & Point::operator-=(const Point & point)
{
    return this->operator+=(-point);
}

Point Point::operator-(const Point & point)
{
    return this->operator+(-point);
}

Point & Point::operator*=(float value)
{
    this->Scale(value);
    return (*this);
}

Point Point::operator*(float value) const
{
    Point p(*this);
    p *= value;
    return p;
}

Point & Point::operator/=(float value)
{
    return ((*this)*=(1.f/value));
}

Point Point::operator/(float value) const
{
    return ((*this)*(1.f/value));
}


std::ostream & operator << (std::ostream & out, const Point & point)
{
    return out << "Point : Position (" << point.GetX() << " ; " << point.GetY() << ")";
}
