#pragma once
class Vector2
{
public:
	Vector2();				// ºİ½Ä×¸À
	Vector2(int x, int y);	// ˆø”•t‚«‚Ìºİ½Ä×¸À
	~Vector2();				// ÃŞ½Ä×¸À
	int x;					// xÀ•W 
	int y;					// yÀ•W

	// ‘ã“ü‰‰Zq
	Vector2& operator = (const Vector2& vec);

	// “Y‚¦š‰‰Zq
	int& operator[](int i);

	// ”äŠr‰‰Zq
	bool operator==(const Vector2& vec) const;
	bool operator!=(const Vector2& vec) const;
	bool operator<=(const Vector2& vec) const;
	bool operator<(const Vector2& vec) const;
	bool operator>=(const Vector2& vec) const;
	bool operator>(const Vector2& vec) const;

	// ’P€‰‰Zq

	Vector2& operator+=(const Vector2& vec);
	Vector2& operator-=(const Vector2& vec);
	Vector2& operator*=(int k);
	Vector2& operator/=(int k);
	Vector2 operator+()const;
	Vector2 operator-()const;
};

// ÍŞ¸ÄÙ‚Ì‰‰Z
// Vector2 + int
Vector2 operator+(const Vector2& v, const int k);
// Vector2 - int
Vector2 operator-(const Vector2& v, const int k);
// Vector2 + Vector2
Vector2 operator+(const Vector2& v, const Vector2& u);
// Vector2 - Vector2
Vector2 operator-(const Vector2& v, const Vector2& u);
// int * Vector2
Vector2 operator*(const int k, const Vector2& v);
// Vector2 * int
Vector2 operator*(const Vector2& v, const int k);
// Vector2 / int
Vector2 operator/(const Vector2& v, const int k);
// Vector2 % int
Vector2 operator%(const Vector2& v, const int k);
