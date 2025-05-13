#pragma once
#include <cmath>
struct Vector2D //우리의 좌표를 책임져줄 친구입니다.
{
	float x;
	float y;
	Vector2D() :x(0), y(0) { }
	Vector2D(float x, float y) :x(x), y(y) { }
	Vector2D operator+(const Vector2D& obj) const;
	Vector2D operator-(const Vector2D& obj) const;
	Vector2D operator*(const float obj) const;
	Vector2D operator/(const float obj) const;
	Vector2D operator=(const Vector2D& obj);
	Vector2D& operator+=(const Vector2D& obj);
	Vector2D& operator-=(const Vector2D& obj);
	Vector2D& operator*=(const float obj);
	Vector2D& operator/=(const float obj);
	Vector2D& operator-();
	bool operator==(const Vector2D& obj) const;
	bool operator!=(const Vector2D& obj) const;
	Vector2D& Normalize();
	float Length();


};
inline Vector2D Vector2D::operator+(const Vector2D& obj) const
{
	return Vector2D(this->x + obj.x, this->y + obj.y);
}

inline Vector2D Vector2D::operator-(const Vector2D& obj) const
{
	return Vector2D(this->x - obj.x, this->y - obj.y);
}

inline Vector2D Vector2D::operator*(const float obj) const
{
	return Vector2D(this->x * obj, this->y * obj);
}

inline Vector2D Vector2D::operator/(const float obj) const
{
	assert(obj != 0);
	return Vector2D(this->x / obj, this->y / obj);
}
inline bool Vector2D::operator==(const Vector2D& obj) const
{
	if (x == obj.x && y == obj.y)
		return true;
	return false;
}

inline Vector2D Vector2D::operator=(const Vector2D& obj) 
{
	return Vector2D(this->x = obj.x, this->y = obj.y);
}

inline Vector2D& Vector2D::operator+=(const Vector2D& obj)
{
	x += obj.x;
	y += obj.y;
	return *this;
}

inline Vector2D& Vector2D::operator-=(const Vector2D& obj)
{
	x -= obj.x;
	y -= obj.y;
	return *this;
}

inline Vector2D& Vector2D::operator*=(const float obj)
{
	x *= obj;
	y *= obj;
	return *this;
}

inline Vector2D& Vector2D::operator/=(const float obj)
{
	assert(obj != 0, "Divide by 0");
	x /= obj;
	y /= obj;
}

inline Vector2D& Vector2D::operator-()
{
	x = -x;
	y = -y;
	return *this;
}

inline bool Vector2D::operator!=(const Vector2D& obj) const
{
	if (x == obj.x && y == obj.y)
		return false;
	return true;
}

inline float Vector2D::Length()
{
	return sqrt(x * x + y * y);
}

inline Vector2D& Vector2D::Normalize()
{
	float length = Length();
	if (length == 0)
		return *this;
	x /= length;
	y /= length;
	return *this;
}
