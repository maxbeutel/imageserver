#include "imageserver/image/ConfigurationFileContext.hpp"

#include <stdio.h>

ConfigurationFileContext::ConfigurationFileContext()
{
}

int ConfigurationFileContext::resizeImage(lua_State *) {
  printf("resize image\n");

  return 1;
}

int ConfigurationFileContext::cropImage(lua_State *) {
  printf("crop image\n");

  return 1;
}
