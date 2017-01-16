#pragma once

#include <lua5.3/lua.hpp>

class ImageFilterConfigurationContext
{
 public:
  ImageFilterConfigurationContext();

  int resizeImage(lua_State *L);
  int cropImage(lua_State *L);
};
