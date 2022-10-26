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
	Vec2		LeftTopPos;		//좌상단 좌표
	Vec2		Size;			//프레임 사이즈
	Vec2		Offset;			//추가이동
	FLOAT		Duration;		//해당 프레임 노출 시간
};

struct tMonsterInfo
{
	UINT		m_iHP;
	UINT		m_iMaxHP;

	float		m_fAtt;					//공격력
	float		m_fDef;					//방어력
	float		m_fAgi;					//민첩성

	float		m_fSpeed;				//속도
	float		m_fDetectRange;			//탐지범위
	float		m_fAttRange;			//공격범위
};