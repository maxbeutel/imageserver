#include <stdio.h>

#include "imageserver/image/ImageFilterConfigurationContext.hpp"

ImageFilterConfigurationContext::ImageFilterConfigurationContext(
    std::unique_ptr<ImageService> imageService,
    const ResolvedFile image
                                                                 )
    : imageService(std::move(imageService)), image(std::move(image))
{
}

int ImageFilterConfigurationContext::loadImage(lua_State *L)
{
  // clients are expected to call this method in the lua script
  printf("loading image\n");
  inputImage = imageService->loadImage(image);

  return 1;
}

int ImageFilterConfigurationContext::getImageWidth(lua_State *)
{
  printf("get image width\n");
  auto imageSize = imageService->getImageSize(inputImage);

  return 1;
}

int ImageFilterConfigurationContext::getImageHeight(lua_State *)
{
  printf("get image height\n");
  auto imageSize = imageService->getImageSize(inputImage);

  return 1;
}

int ImageFilterConfigurationContext::resizeImage(lua_State *)
{
  printf("resize image\n");

  return 1;
}

int ImageFilterConfigurationContext::cropImage(lua_State *)
{
  printf("crop image\n");

  return 1;
}

int ImageFilterConfigurationContext::writeImage(lua_State *)
{
  printf("writing image (to cache path?)\n");

  return 1;
}
