// The MIT License (MIT)
// 
// Copyright (c) 2015 Matthew J. Runyan
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "include/lua.h"
#include "include/lauxlib.h"

char enabled = 1;

void CoYield_Yield(lua_State *L, lua_Debug *ar)
{
	if (enabled)
	{
		enabled = 0;
		lua_yield(L, 0);
	}
}

int CoYield_MakeCoYield(lua_State *L)
{
	luaL_checktype(L, 1, LUA_TTHREAD);
	lua_State *L1 = lua_tothread(L, 1);
	lua_sethook(L1, CoYield_Yield, LUA_MASKCOUNT, 1000);
	return 0;
}

int CoYield_ReenableYield(lua_State *L)
{
	enabled = 1;
	return 0;
}

static const struct luaL_reg CoYield [] = {
      {"MakeCoYield", CoYield_MakeCoYield},
      {"ReenableYield", CoYield_ReenableYield},
      {NULL, NULL}
};

int luaopen_libCoYield (lua_State *L)
{
	luaL_register(L, NULL, CoYield);
	return 1;
}
