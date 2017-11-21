/*************************************************
Author:            |メ破坏者☆
Date:              |2017-02-28
version：          |0.0.1
Description:       |颜色插件主要函数
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
bool loop = true;//传递关闭插件信号
				 /*************************************************
				 Function:         |task
				 Description:      |颜色插件的主体功能
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
Description:      |开启颜色插件功能
Calls:            |task
Others:           |此函数供lua脚本调用
*************************************************/
static int start(lua_State* L) {
	HANDLE hThread = CreateThread(NULL, 0, task, NULL, 0, NULL);
	return 0;
}
/*************************************************
Function:         |stop
Description:      |关闭颜色插件功能
Others:           |此函数供lua脚本调用
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