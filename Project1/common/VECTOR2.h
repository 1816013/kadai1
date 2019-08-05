#pragma once

template<class T>
class Vector2Temple
{
public:
	Vector2Temple();				// ºİ½Ä×¸À
	Vector2Temple(T x, T y);	// ˆø”•t‚«‚Ìºİ½Ä×¸À
	~Vector2Temple();				// ÃŞ½Ä×¸À
	T x;					// xÀ•W 
	T y;					// yÀ•W

	// ‘ã“ü‰‰Zq
	Vector2Temple& operator = (const Vector2Temple& vec);

	// “Y‚¦š‰‰Zq
	int& operator[](int i);

	// ”äŠr‰‰Zq
	bool operator==(const Vector2Temple& vec) const;
	bool operator!=(const Vector2Temple& vec) const;
	bool operator<=(const Vector2Temple& vec) const;
	bool operator<(const Vector2Temple& vec) const;
	bool operator>=(const Vector2Temple& vec) const;
	bool operator>(const Vector2Temple& vec) const;

	// ’P€‰‰Zq
	Vector2Temple& operator+=(const Vector2Temple& vec);
	Vector2Temple& operator+=(T k);
	Vector2Temple& operator-=(const Vector2Temple& vec);
	Vector2Temple& operator*=(T k);
	Vector2Temple& operator*=(const Vector2Temple& vec);
	Vector2Temple& operator/=(T k);
	Vector2Temple operator+()const;
	Vector2Temple operator-()const;
};

// ÍŞ¸ÄÙ‚Ì‰‰Z
// Vector2Temple + int
template<class T>
Vector2Temple<T> operator+(const Vector2Temple<T>& v, const T k);
// Vector2Temple - int
template<class T>
Vector2Temple<T> operator-(const Vector2Temple<T>& v, const T k);
// Vector2Temple + Vector2Temple
template<class T>
Vector2Temple<T> operator+(const Vector2Temple<T>& v, const Vector2Temple<T>& u);
// Vector2Temple - Vector2Temple
template<class T>
Vector2Temple<T> operator-(const Vector2Temple<T>& v, const Vector2Temple<T>& u);
// int * Vector2Temple
template<class T>
Vector2Temple<T> operator*(const int k, const Vector2Temple<T>& v);
// Vector2Temple * int
template<class T>
Vector2Temple<T> operator*(const Vector2Temple<T>& v, const T k);
// Vector2Temple / int
template<class T>
Vector2Temple<T> operator/(const Vector2Temple<T>& v, const T k);
// Vector2Temple % int
template<class T>
Vector2Temple<T> operator%(const Vector2Temple<T>& v, const T k);

using Vector2 = Vector2Temple<int>;
using Vector2_D = Vector2Temple<double>;
using Vector2_F = Vector2Temple<float>;

#include"./details/VECTOR2.h"