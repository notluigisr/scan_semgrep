int luaSetResp(lua_State *lua) {
    int argc = lua_gettop(lua);

    if (argc != 1) {
        lua_pushstring(lua, "STR");
        return lua_error(lua);
    }

    int resp = lua_tonumber(lua,-argc);
    if (resp != 2 && resp != 3) {
        lua_pushstring(lua, "STR");
        return lua_error(lua);
    }

    server.lua_client->resp = resp;
    return 0;
}