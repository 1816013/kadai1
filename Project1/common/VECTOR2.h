#pragma once
class Vector2
{
public:
	Vector2();				// �ݽ�׸�
	Vector2(int x, int y);	// �����t���̺ݽ�׸�
	~Vector2();				// �޽�׸�
	int x;					// x���W 
	int y;					// y���W

	// ������Z�q
	Vector2& operator = (const Vector2& vec);

	// �Y�������Z�q
	int& operator[](int i);

	// ��r���Z�q
	bool operator==(const Vector2& vec) const;
	bool operator!=(const Vector2& vec) const;
	bool operator<=(const Vector2& vec) const;
	bool operator<(const Vector2& vec) const;
	bool operator>=(const Vector2& vec) const;
	bool operator>(const Vector2& vec) const;

	// �P�����Z�q

	Vector2& operator+=(const Vector2& vec);
	Vector2& operator-=(const Vector2& vec);
	Vector2& operator*=(int k);
	Vector2& operator/=(int k);
	Vector2 operator+()const;
	Vector2 operator-()const;
};

// �޸�ق̉��Z
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
