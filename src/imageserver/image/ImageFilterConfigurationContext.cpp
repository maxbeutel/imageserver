#include <stdio.h>

#include "imageserver/image/ImageFilterConfigurationContext.hpp"

ImageFilterConfigurationContext::ImageFilterConfigurationContext()
{
}

int ImageFilterConfigurationContext::resizeImage(lua_State *) {
  printf("resize image\n");

  return 1;
}

int ImageFilterConfigurationContext::cropImage(lua_State *) {
  printf("crop image\n");

  return 1;
}
