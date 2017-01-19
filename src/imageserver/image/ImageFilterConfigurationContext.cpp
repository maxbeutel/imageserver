#include <stdio.h>
#include <assert.h>

#include "imageserver/image/ImageFilterConfigurationContext.hpp"

ImageFilterConfigurationContext::ImageFilterConfigurationContext(
    std::unique_ptr<ImageService> imageService,
    const ResolvedFile image
                                                                 )
    : imageService(std::move(imageService)), image(image)
{
}

// @FIXME assert in every function that inputImage is not NULL/empty? cv::Mat.empty()

int ImageFilterConfigurationContext::loadImage(lua_State *)
{
  // clients are expected to call this method in the lua script
  printf("loading image\n");
  inputImage = imageService->loadImage(image);

  // @TODO catch error when image could not be loaded
  // and let the lua script know about this

  return 0;
}

int ImageFilterConfigurationContext::getImageWidth(lua_State *L)
{
  assert(L != NULL && "Lua state variable is NULL.");

  printf("get image width\n");
  auto imageSize = imageService->getImageSize(inputImage);
  lua_pushnumber(L, imageSize.first);

  return 1;
}

int ImageFilterConfigurationContext::getImageHeight(lua_State *L)
{
  assert(L != NULL && "Lua state variable is NULL.");

  printf("get image height\n");
  auto imageSize = imageService->getImageSize(inputImage);
  lua_pushnumber(L, imageSize.second);

  return 1;
}

int ImageFilterConfigurationContext::resizeImage(lua_State *L)
{
  assert(L != NULL && "Lua state variable is NULL.");

  luaL_checkany(L, 1);
  luaL_checkany(L, 2);

  int height = static_cast<int>(lua_tonumber(L, lua_gettop(L)));
  lua_pop(L, 1);

  luaL_argcheck(L, height > 0, 2, "height must be > 0");

  int width = static_cast<int>(lua_tonumber(L, lua_gettop(L)));
  lua_pop(L, 1);

  luaL_argcheck(L, width > 0, 1, "width must be > 0");



  printf("resize image - width: %d, height %d\n", width, height);

  return 0;
}

int ImageFilterConfigurationContext::cropImage(lua_State *L)
{
  luaL_checkany(L, 1);
  luaL_checkany(L, 2);

  int height = static_cast<int>(lua_tonumber(L, lua_gettop(L)));
  lua_pop(L, 1);

  luaL_argcheck(L, height > 0, 2, "height must be > 0");

  int width = static_cast<int>(lua_tonumber(L, lua_gettop(L)));
  lua_pop(L, 1);

  luaL_argcheck(L, width > 0, 1, "width must be > 0");



  printf("crop image - width: %d, height %d\n", width, height);

  return 0;
}

int ImageFilterConfigurationContext::writeImage(lua_State *L)
{
  assert(L != NULL && "Lua state variable is NULL.");

  luaL_checkany(L, 1);

  const char *path = lua_tostring(L, 1);
  size_t path_len = lua_rawlen(L, -1);

  luaL_argcheck(L, path[path_len] == '\0', 1, "path argument not 0-terminated");
  luaL_argcheck(L, path_len > 0, 1, "path argument is empty");

  printf("writing image (to cache path?): %s\n", path);

  return 0;
}
