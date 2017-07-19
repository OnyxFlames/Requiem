#pragma once

extern "C"
{
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lapi.h"
#include "lua/lauxlib.h"
}

lua_State* init_lua();
