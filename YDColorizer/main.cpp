/*************************************************
Author:            |���ƻ��ߡ�
Date:              |2017-02-28
version��          |0.0.1
Description:       |��ɫ�����Ҫ����
**************************************************/
#include <windows.h>
//#include "Config.h"
//#include "Language.h"
//#include "WinFind.h"
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};
bool loop = true;//���ݹرղ���ź�
				 /*************************************************
				 Function:         |task
				 Description:      |��ɫ��������幦��
				 *************************************************/
DWORD WINAPI task(LPVOID lpParamter) {
	MessageBox(NULL, TEXT(""), TEXT(""), MB_ICONERROR);
	while (loop) {
		Sleep(1000);
	}
	return 0;
}
/*************************************************
Function:         |start
Description:      |������ɫ�������
Calls:            |task
Others:           |�˺�����lua�ű�����
*************************************************/
static int start(lua_State* L) {
	HANDLE hThread = CreateThread(NULL, 0, task, NULL, 0, NULL);
	return 0;
}
/*************************************************
Function:         |stop
Description:      |�ر���ɫ�������
Others:           |�˺�����lua�ű�����
*************************************************/
static int stop(lua_State *L) {
	loop = false;
	return 0;
}
static const luaL_Reg MyLuaDLLFunctions[] =
{
	{ "start", start },
	{ "stop", stop }
};
#ifdef _WIN32  
extern "C" __declspec(dllexport) int luaopen_luadlllib(lua_State* L)
#else  
extern "C"  int luaopen_luadlllib(lua_State* L)
#endif
{
	lua_newtable(L);
	luaL_setfuncs(L, MyLuaDLLFunctions, 0);
	return 1;
}