#include "EvaluatedImageProcessingConfigurationImpl.hpp"

#include <stdio.h>

EvaluatedImageProcessingConfigurationImpl::EvaluatedImageProcessingConfigurationImpl()
{
}

int EvaluatedImageProcessingConfigurationImpl::resizeImage(lua_State *) {
  printf("resize image\n");

  return 1;
}

int EvaluatedImageProcessingConfigurationImpl::cropImage(lua_State *) {
  printf("crop image\n");

  return 1;
}
