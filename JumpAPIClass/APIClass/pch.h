#pragma once


#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <crtdbg.h>

#include <assert.h>

#include <vector>
#include <list>
#include <map>
#include <string>



//원래는 std::vector를 풀 네임으로 써야되는데 using를 사용함으로써 std::vector => vector로 사용이 가능하다.
//사용자가 임의의 변수를 만들때 vector로 이름을 지으면 충돌이 일어나기에. 상황에 맞게 잘 사용하는게 좋다.
using std::vector;
using std::list;
using std::map;
using std::make_pair;

using std::string;
using std::wstring;
//문자열을 관리해주는 클래스이다 string는 4바이트, wstring는 1바이트


#include "def.h"
#include "struct.h"
#include "Func.h"


#pragma comment (lib, "Msimg32.lib")



