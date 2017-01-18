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
    std::ostream &logOutputStream
                                     ) const
{
  int status, result;
  lua_State *L;

  L = luaL_newstate();
  luaL_openlibs(L);

  auto configurationFileContext = std::make_unique<ImageFilterConfigurationContext>(
      std::make_unique<ImageService>(),
      image
                                                                                    );

  *static_cast<ImageFilterConfigurationContext**>(lua_getextraspace(L)) = configurationFileContext.get();
  lua_register(L, "image_get_width", &dispatch<&ImageFilterConfigurationContext::getImageWidth>);
  lua_register(L, "image_get_height", &dispatch<&ImageFilterConfigurationContext::getImageHeight>);
  lua_register(L, "image_resize", &dispatch<&ImageFilterConfigurationContext::resizeImage>);
  lua_register(L, "image_crop", &dispatch<&ImageFilterConfigurationContext::cropImage>);

  status = luaL_loadfile(L, configurationFile.getFullPath().c_str());

  if (status) {
    fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(L, -1));
    // @FIXME return here, file not found
  }

  result = lua_pcall(L, 0, LUA_MULTRET, 0);

  if (result) {
    fprintf(stderr, "Failed to run script: %s\n", lua_tostring(L, -1));
    // @FIXME return here, failed to run script, e. g. syntax error
  }

  // get value that the lua script returned (if any)
  // dumping it to the output stream, useful for debugging
  const char *res = lua_tostring(L, -1);
  logOutputStream << res;

  lua_pop(L, 1);
  lua_close(L);
}
