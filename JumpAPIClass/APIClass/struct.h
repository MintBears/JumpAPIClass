#pragma once

struct Vec2
{
public : 
	float x;
	float y;

public :
	Vec2() :
		x(0.f),
		y(0.f)
	{

	}

	Vec2(float _x, float _y) :
		x(_x),
		y(_y)
	{

	}

	Vec2(UINT _x, UINT _y) :
		x((float)_x),
		y((float)_y)
	{

	}
	Vec2(POINT _point) :
		x((float)_point.x),
		y((float)_point.y)
	{

	}

	~Vec2()
	{

	}


public:

	bool IsZero()
	{
		return x == 0.f && y == 0.f;
	}

	void Normalize()
	{
		float Dist = sqrtf(x * x + y * y);
		x /= Dist;
		y /= Dist;
	}

	float Length()
	{
		return sqrtf(x * x + y * y);
	}
	//+
	Vec2 operator + (Vec2 _other)
	{
		return Vec2(x + _other.x, y + _other.y);
	}

	Vec2 operator += (Vec2 _other)
	{
		return Vec2(x += _other.x, y += _other.y);
	}
	//-
	Vec2 operator - (Vec2 _other)
	{
		return Vec2(x - _other.x, y - _other.y);
	}

	Vec2 operator -= (Vec2 _other)
	{
		return Vec2(x -= _other.x, y -= _other.y);
	}
	//*
	Vec2 operator * (Vec2 _other)
	{
		return Vec2(x * _other.x, y * _other.y);
	}
	Vec2 operator * (float _other)
	{
		return Vec2(x * _other, y * _other);
	}

	Vec2 operator *= (Vec2 _other)
	{
		return Vec2(x *= _other.x, y *= _other.y);
	}

	Vec2 operator *= (float _other)
	{
		return Vec2(x *= _other, y *= _other);
	}
	///
	Vec2 operator / (Vec2 _other)
	{
		return Vec2(x / _other.x, y / _other.y);
	}
	Vec2 operator / (float _other)
	{
		return Vec2(x / _other, y / _other);
	}

	Vec2 operator /= (Vec2 _other)
	{
		return Vec2(x /= _other.x, y /= _other.y);
	}

	Vec2 operator /= (float _other)
	{
		return Vec2(x /= _other, y /= _other);
	}
	//
	Vec2 operator -()
	{
		return Vec2(-x, -y);
	}

};

struct tEvent
{
	EVENT_TYPE	eType;
	DWORD_PTR	wParam;
	DWORD_PTR	lParam;
};

struct tAnimFrm
{
	Vec2		LeftTopPos;		//�»�� ��ǥ
	Vec2		Size;			//������ ������
	Vec2		Offset;			//�߰��̵�
	FLOAT		Duration;		//�ش� ������ ���� �ð�
};