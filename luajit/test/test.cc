#include <stdio.h>
#include <assert.h>
#include "luajit/lua.hpp"

int main(int argc, char *argv[]) {

    lua_State *L = lua_open();
    assert(L);

    luaL_openlibs(L);

    int result = luaL_dostring(L, "print(\"hello world\")");
    assert(result == 0);

    result = luaL_dostring(L, "local i = 1; print(i + 100)");
    assert(result == 0);


    lua_close(L);
    printf("ok\n");
    return 0;
}
