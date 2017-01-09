#pragma once

#include <lua5.3/lua.hpp>

// @FIXME doesn't make sense to use the PIMPL idiom here anymore, because
// EvaluatedImageProcessingConfiguration won't hold a pointer to this implementation

class EvaluatedImageProcessingConfigurationImpl
{
 public:
  EvaluatedImageProcessingConfigurationImpl();

  int resizeImage(lua_State *L);
  int cropImage(lua_State *L);
};
