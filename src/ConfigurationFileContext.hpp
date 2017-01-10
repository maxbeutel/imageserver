#pragma once

#include <lua5.3/lua.hpp>

class ConfigurationFileContext
{
 public:
  ConfigurationFileContext();

  int resizeImage(lua_State *L);
  int cropImage(lua_State *L);
};
