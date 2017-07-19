#include "Lua_Main.hpp"

lua_State* init_lua()
{
	lua_State *L;
	L = luaL_newstate();
	luaL_openlibs(L);
	return L;
}