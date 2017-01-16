#include <lua5.3/lua.hpp>

#include "imageserver/image/ImageFilterService.hpp"
#include "imageserver/image/ImageFilterConfigurationContext.hpp"

typedef int (ImageFilterConfigurationContext::*mem_func)(lua_State * L);

template <mem_func func>
int dispatch(lua_State * L) {
  ImageFilterConfigurationContext* ptr = *static_cast<ImageFilterConfigurationContext**>(lua_getextraspace(L));
  return ((*ptr).*func)(L);
}

ImageFilterService::ImageFilterService()
{
}

void ImageFilterService::filterImage(
    const ResolvedFile &configurationFile,
    const ResolvedFile &image,
    const std::map<std::string, std::string> &parameters,
    std::ostream &configurationFileOutputStream
                                     ) const
{
  // int status, result;
  // lua_State *L;

  // L = luaL_newstate();
  // luaL_openlibs(L);

  // // @FIXME pass pointers to private functions here, so that clients cant see this configuration methods?
  // auto impl = std::make_unique<ConfigurationFileContext>();
  // *static_cast<ConfigurationFileContext**>(lua_getextraspace(L)) = impl.get();
  // lua_register(L, "image_resize", &dispatch<&ConfigurationFileContext::resizeImage>);
  // lua_register(L, "image_crop", &dispatch<&ConfigurationFileContext::cropImage>);

  // status = luaL_loadfile(L, configurationFileFullPath.c_str());

  // if (status) {
  //   fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(L, -1));
  //   // @FIXME return here, file not found
  // }

  // lua_newtable(L);

  // for (auto const &kv : parameters) {
  //   lua_pushstring(L, kv.first.c_str());
  //   lua_pushstring(L, kv.second.c_str());
  //   lua_rawset(L, -3);
  // }

  // lua_setglobal(L, "imageData");

  // result = lua_pcall(L, 0, LUA_MULTRET, 0);

  // if (result) {
  //   fprintf(stderr, "Failed to run script: %s\n", lua_tostring(L, -1));
  //   // @FIXME return here, failed to run script, e. g. syntax error
  // }

  // // get value that the lua script returned (if any)
  // // returning to the output stream, useful for debugging
  // const char *res = lua_tostring(L, -1);
  // configurationFileOutputStream << res;

  // lua_pop(L, 1);
  // lua_close(L);

  // return EvaluatedImageProcessingConfiguration::createFromConfigurationFileContext(impl);
}
