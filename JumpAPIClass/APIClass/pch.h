#pragma once


#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����
#include <windows.h>
// C ��Ÿ�� ��� �����Դϴ�.
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



//������ std::vector�� Ǯ �������� ��ߵǴµ� using�� ��������ν� std::vector => vector�� ����� �����ϴ�.
//����ڰ� ������ ������ ���鶧 vector�� �̸��� ������ �浹�� �Ͼ�⿡. ��Ȳ�� �°� �� ����ϴ°� ����.
using std::vector;
using std::list;
using std::map;
using std::make_pair;

using std::string;
using std::wstring;
//���ڿ��� �������ִ� Ŭ�����̴� string�� 4����Ʈ, wstring�� 1����Ʈ


#include "def.h"
#include "struct.h"
#include "Func.h"


#pragma comment (lib, "Msimg32.lib")



