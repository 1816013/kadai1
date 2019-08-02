#include "..\VECTOR2.h"
#pragma once
//#include "../VECTOR2.h"	// ‚È‚­‚Ä‚à‚æ‚¢
// detail

// ¸×½“à
template<class T>
Vector2Temple<T>::Vector2Temple()
{
	x = 0;
	y = 0;
}

template<class T>
Vector2Temple<T>::Vector2Temple(T x, T y)
{
	this->x = x;
	// (*this).x = x; ‚±‚ê‚à“¯‚¶(CŒ¾Œê‚Å‚à‚©‚¯‚é‘‚«•û)
	this->y = y;
}

template<class T>
Vector2Temple<T>::~Vector2Temple()
{

}

template<class T>
Vector2Temple<T> & Vector2Temple<T>::operator=(const Vector2Temple & vec)
{
	x = vec.x;
	y = vec.y;
	return *this;
}

template<class T>
int & Vector2Temple<T>::operator[](int i)
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

template<class T>
bool Vector2Temple<T>::operator==(const Vector2Temple & vec) const
{
	return ((this->x == vec.x) && (this->y == vec.y));
	/*if (this->x == vec.x && this->y == vec.y) 
	{
		return true;
	}
	return false;*/
}

template<class T>
bool Vector2Temple<T>::operator!=(const Vector2Temple & vec) const
{
	return (!(this->x == vec.x) && !(this->y == vec.y));
	//return !((this->x == vec.x) && (this->y == vec.y));
}

template<class T>
bool Vector2Temple<T>::operator<=(const Vector2Temple & vec) const
{
	return ((this->x <= vec.x) && (this->y <= vec.y));
}

template<class T>
bool Vector2Temple<T>::operator<(const Vector2Temple & vec) const
{
	return ((this->x < vec.x) && (this->y < vec.y));
}

template<class T>
bool Vector2Temple<T>::operator>=(const Vector2Temple & vec) const
{
	return ((this->x >= vec.x) && (this->y >= vec.y));
}

template<class T>
bool Vector2Temple<T>::operator>(const Vector2Temple & vec) const
{
	return ((this->x > vec.x) && (this->y > vec.y));
}

template<class T>
Vector2Temple<T> & Vector2Temple<T>::operator+=(const Vector2Temple & vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return (*this);
}

template<class T>
inline Vector2Temple<T> & Vector2Temple<T>::operator+=(T k)
{
	this->x += k;
	this->y += k;
	return (*this);
}

template<class T>
Vector2Temple<T> & Vector2Temple<T>::operator-=(const Vector2Temple & vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return (*this);
}

template<class T>
Vector2Temple<T> & Vector2Temple<T>::operator*=(T k)
{
	this->x *= k;
	this->y *= k;
	return (*this);
}

template<class T>
inline Vector2Temple<T> & Vector2Temple<T>::operator*=(const Vector2Temple & vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	return (*this);
}

template<class T>
Vector2Temple<T> & Vector2Temple<T>::operator/=(T k)
{
	this->x /= k;
	this->y /= k;
	return (*this);
}

template<class T>
Vector2Temple<T> Vector2Temple<T>::operator+() const
{
	return *this;
}

template<class T>
Vector2Temple<T> Vector2Temple<T>::operator-() const
{
	return Vector2Temple(-this->x, -this->y);
}

// ¸×½‚ÌŠO
template<class T>
Vector2Temple<T> operator+(const Vector2Temple<T> & v, T k)
{
	Vector2Temple vec;
	vec.x = v.x + k;
	vec.y = v.y + k;
	return vec;
	//return Vector2Temple(v.x + k, v.y + k);
}

template<class T>
Vector2Temple<T> operator-(const Vector2Temple<T> & v, T k)
{
	/*Vector2Temple vec;
	vec.x = v.x - k;
	vec.y = v.y - k;
	return vec;*/
	return Vector2Temple<T>(v.x - k, v.y - k);
}

template<class T>
Vector2Temple<T> operator+(const Vector2Temple<T> & v, const Vector2Temple<T> & u)
{
	return Vector2Temple<T>(v.x + u.x, v.y + u.y);
}

template<class T>
Vector2Temple<T> operator-(const Vector2Temple<T> & v, const Vector2Temple<T> & u)
{
	return Vector2Temple<T>(v.x - u.x, v.y - u.y);
}

template<class T>
Vector2Temple<T> operator*(const int k, const Vector2Temple<T> & v)
{
	return Vector2Temple<T>(k * v.x, k * v.y);
}

template<class T>
Vector2Temple<T> operator*(const Vector2Temple<T> & v, const T k)
{
	return Vector2Temple<T>(v.x * k, v.y * k);
}

template<class T>
Vector2Temple<T> operator/(const Vector2Temple<T> & v, const T k)
{
	return Vector2Temple<T>(v.x / k, v.y / k);
}

template<class T>
Vector2Temple<T> operator%(const Vector2Temple<T> & v, const T k)
{
	return Vector2Temple<T>(v.x % k, v.y % k);
}
