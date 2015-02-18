#include "Circle.h"

Circle::~Circle()
{

}

Circle::Circle()
{
	this->_radius = 0.f;
}

Circle::Circle(const Point & point, float radius)
{
	this->_center = point;
	this->_radius = radius;
}

Circle::Circle(const Circle & circle)
{
	this->_center = circle._center;
	this->_radius = circle._radius;
}

void Circle::Add(const Point & point)
{
	this->_center.Add(point);
}

void Circle::Scale(float scale)
{
	this->_center.Scale(scale);
	this->_radius *= scale;
}

bool Circle::Include(const Point & point) const
{
	return (this->_center.Distance(point)) <= (this->_radius);
}

bool Circle::Intersect(const Circle & circle) const
{
	return (this->_center.Distance(circle._center)) <= (this->_radius + circle._radius);
}

float Circle::Area() const
{
	return (M_PI * this->_radius * this->_radius);
}

float Circle::Perimeter() const
{
	return (2 * M_PI * this->_radius);
}

Point Circle::Center() const
{
	return this->_center;
}

void Circle::SetCenter(const Point & center)
{
	this->_center = center;
}

void Circle::SetRadius(float radius)
{
	this->_radius = radius;
}

Point Circle::GetCenter() const
{
	return this->_center;
}

float Circle::GetRadius() const
{
	return this->_radius;
}

Circle & Circle::operator+=(const Point & point)
{
	this->Add(point);
	return (*this);
}

Circle Circle::operator+(const Point & point) const
{
	Circle c(*this);
	c += point;
	return c;
}

Circle & Circle::operator-=(const Point & point)
{

	return ((*this) += (-point));
}

Circle Circle::operator-(const Point & point)
{
	Circle c = (*this);
	c -= point;
	return c;
}

Circle & Circle::operator*=(float value)
{
	this->Scale(value);
	return (*this);
}

Circle Circle::operator*(float value) const
{
	Circle c(*this);
	return (c *= value);
}

Circle & Circle::operator/=(float value)
{
	return ((*this) *= (1.f / value));
}

Circle Circle::operator/(float value) const
{
	return ((*this)*(1.f / value));
}

std::ostream & operator << (std::ostream & out, const Circle & circle)
{
	return out << "Circle data : Center(" << circle.GetCenter().GetX() << ";" << circle.GetCenter().GetY() << ") | Radius : " << circle.GetRadius();
}
