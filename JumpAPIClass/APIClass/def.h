#pragma once

#define SINGLE(type) public : static type* GetInst(){static type inst; return &inst;}\
					 private : type(); ~type();

#define DT CTimeMgr::GetInst()->GetDeltaTime()

#define IsTap(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::TAP
#define IsPressed(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::PRESSED
#define IsRelease(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::RELEASED
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()

#define DEL(p) if (nullptr != p) delete p;
#define PI	3.1215926535f

#define CLONE(type)	virtual type* Clone() { return new type(*this); }
#define CLONE_DEACTIVATE(type)	virtual type* Clone() { assert(nullptr); return nullptr; }

#define	TILE_SIZE 64

enum class LEVEL_TYPE
{
	START,
	STAGE_01,
	STAGE_02,
	STAGE_03,
	STAGE_04,

	EDITOR,

	END,

};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,

	END,
};

enum class LAYER
{
	BACKGROUND,
	TILE,
	PLATFORM,
	DEFAULT,
	PLAYER,
	MONSTER,
	PLAYER_PROJECTILE,
	MONSTER_PROJECTILE,

	FORCE,

	UI = 15,
	END = 16,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,			//오브젝트 생성 //wParam : Object Adress			//lParam : Layer type
	DELETE_OBJECT,			//오즈벡트 제거 //wParam : Object Adress
	LEVEL_CHANGE,			//레벨 교환	   //wParam : Level_type(Next Level Type)
	CHANGE_AI_STATE,		//ai교환		   //wParam : ai Component Adress	//lParam : Next State Name
};

enum class CAMERA_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};


















/*
public:
	//정적싱글톤
	//처음부터 데이터 영역에 자리가 마련되여있으며, 항상 준비되어있다.
	//하지만 시간이 지날수록 데이터가 누적되어서 불필요한 데이터가 생길수 있다.
	static CEngine* GetInst()
	{
		static CEngine engine;
		return &engine;
	}

	//정적이되 동적으로 활용되는 싱글톤
	//정적 포인터 변수를 만들어 데이터 영역에 주소값을 저장후, 힙영역에 객체를 담아두는방식.
	//힙영역에 만드는게 있다면 지우는게 필연적으로 필요하기때문에 Deleta를 만들어 줘야한다.
	//하지만 관리 할수있기에 만들수있고, 일일이 지워주는 관리를 해야된다.
	
private:
	static CEngine* m_pInst;
public:
	static CEngine* GetInit()
	{
		if (nullptr == m_pInst)
		{
			m_pInst = new CEngine;
		}
		return m_pInst;
	}
	static void Delete()
	{
		if (nullptr != m_pInst)
		{
			delete m_pInst;
			m_pInst = nullptr;

		}
	}
	*/