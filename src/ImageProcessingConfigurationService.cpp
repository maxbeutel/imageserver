// for debugging only
#include <stdio.h>

#include <lua5.3/lua.hpp>

#include "ImageProcessingConfigurationService.hpp"
#include "EvaluatedImageProcessingConfigurationImpl.hpp"

typedef int (EvaluatedImageProcessingConfigurationImpl::*mem_func)(lua_State * L);

template <mem_func func>
int dispatch(lua_State * L) {
  EvaluatedImageProcessingConfigurationImpl* ptr = *static_cast<EvaluatedImageProcessingConfigurationImpl**>(lua_getextraspace(L));
  return ((*ptr).*func)(L);
}


ImageProcessingConfigurationService::ImageProcessingConfigurationService()
{
}

std::unique_ptr<EvaluatedImageProcessingConfiguration> ImageProcessingConfigurationService::evaluateConfigurationFile(
    const std::string configurationFileFullPath,
    const std::map<std::string, std::string> &
                                                                                        ) const
{
  int status, result;
  lua_State *L;

  L = luaL_newstate();
  luaL_openlibs(L);

  // @FIXME pass pointers to private functions here, so that clients cant see this configuration methods?
  auto impl = std::make_unique<EvaluatedImageProcessingConfigurationImpl>();
  *static_cast<EvaluatedImageProcessingConfigurationImpl**>(lua_getextraspace(L)) = impl.get();
  lua_register(L, "image_resize", &dispatch<&EvaluatedImageProcessingConfigurationImpl::resizeImage>);
  lua_register(L, "image_crop", &dispatch<&EvaluatedImageProcessingConfigurationImpl::cropImage>);

  status = luaL_loadfile(L, configurationFileFullPath.c_str());

  if (status) {
    fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(L, -1));
    // @FIXME return here, file not found
  }

  // @FIXME create table for parameters that can be used inside the lua script from 2nd parameter to this method
  lua_newtable(L);

  lua_pushstring(L, "width");
  lua_pushnumber(L, 200);
  lua_rawset(L, -3);

  lua_pushstring(L, "height");
  lua_pushnumber(L, 300);
  lua_rawset(L, -3);

  lua_pushstring(L, "fileName");
  lua_pushstring(L, "image.png");
  lua_rawset(L, -3);

  // expose table in lua script
  lua_setglobal(L, "imageData");

  result = lua_pcall(L, 0, LUA_MULTRET, 0);

  if (result) {
    fprintf(stderr, "Failed to run script: %s\n", lua_tostring(L, -1));
    // @FIXME return here, failed to run script, e. g. syntax error
  }

  // get value that the lua script returned (if any)
  // @FIXME we don't actually need this, but maybe keep for debug reasons?
  const char *res = lua_tostring(L, -1);

  printf("Script returned: %s\n", res);

  lua_pop(L, 1);
  lua_close(L);

  return EvaluatedImageProcessingConfiguration::createFromImpl(impl);
}
