#include "VECTOR2.h"

// ¸×½“à
Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(int x, int y)
{
	this->x = x;
	// (*this).x = x; ‚±‚ê‚à“¯‚¶(CŒ¾Œê‚Å‚à‚©‚¯‚é‘‚«•û)
	this->y = y;
}

Vector2::~Vector2()
{

}

Vector2 & Vector2::operator=(const Vector2 & vec)
{
	x = vec.x;
	y = vec.y;
	return *this;
}

int & Vector2::operator[](int i)
{
	if (i == 0) 
	{
		return x;
	}
	else if(i == 1)
	{
		return y;
	}
	else
	{
		return y;
	}
}

bool Vector2::operator==(const Vector2 & vec) const
{
	return ((this->x == vec.x) && (this->y == vec.y));
	/*if (this->x == vec.x && this->y == vec.y) 
	{
		return true;
	}
	return false;*/
}

bool Vector2::operator!=(const Vector2 & vec) const
{
	return (!(this->x == vec.x) && !(this->y == vec.y));
	//return !((this->x == vec.x) && (this->y == vec.y));
}

bool Vector2::operator<=(const Vector2 & vec) const
{
	return ((this->x <= vec.x) && (this->y <= vec.y));
}

bool Vector2::operator<(const Vector2 & vec) const
{
	return ((this->x < vec.x) && (this->y < vec.y));
}

bool Vector2::operator>=(const Vector2 & vec) const
{
	return ((this->x >= vec.x) && (this->y >= vec.y));
}

bool Vector2::operator>(const Vector2 & vec) const
{
	return ((this->x > vec.x) && (this->y > vec.y));
}

Vector2 & Vector2::operator+=(const Vector2 & vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return (*this);
}

Vector2 & Vector2::operator-=(const Vector2 & vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return (*this);
}

Vector2 & Vector2::operator*=(int k)
{
	this->x *= k;
	this->y *= k;
	return (*this);
}

Vector2 & Vector2::operator/=(int k)
{
	this->x /= k;
	this->y /= k;
	return (*this);
}

Vector2 Vector2::operator+() const
{
	return *this;
}

Vector2 Vector2::operator-() const
{
	return Vector2(-this->x, -this->y);
}

// ¸×½‚ÌŠO
Vector2 operator+(const Vector2 & v, int k)
{
	Vector2 vec;
	vec.x = v.x + k;
	vec.y = v.y + k;
	return vec;
	//return Vector2(v.x + k, v.y + k);
}

Vector2 operator-(const Vector2 & v, int k)
{
	/*Vector2 vec;
	vec.x = v.x - k;
	vec.y = v.y - k;
	return vec;*/
	return Vector2(v.x - k, v.y - k);
}

Vector2 operator+(const Vector2 & v, const Vector2 & u)
{
	return Vector2(v.x + u.x, v.y + u.y);
}

Vector2 operator-(const Vector2 & v, const Vector2 & u)
{
	return Vector2(v.x - u.x, v.y - u.y);
}

Vector2 operator*(const int k, const Vector2 & v)
{
	return Vector2(k * v.x, k * v.y);
}

Vector2 operator*(const Vector2 & v, const int k)
{
	return Vector2(v.x * k, v.y * k);
}

Vector2 operator/(const Vector2 & v, const int k)
{
	return Vector2(v.x / k, v.y / k);
}

Vector2 operator%(const Vector2 & v, const int k)
{
	return Vector2(v.x % k, v.y % k);
}
