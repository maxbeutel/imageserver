#pragma once

#include <string>
#include <memory>

#include <lua5.3/lua.hpp>
// @FIXME remove this when ImageService::loadImage returns an opaque handle instead of an openCVMat
#include <opencv2/opencv.hpp>

#include "imageserver/image/ImageService.hpp"
#include "imageserver/filesystem/ResolvedFile.hpp"

class ImageFilterConfigurationContext
{
 private:
  const std::unique_ptr<ImageService> imageService;
  const ResolvedFile image;

  // can't be const because assigned in loadImage method :-|
  cv::Mat inputImage;

 public:
  ImageFilterConfigurationContext(
      std::unique_ptr<ImageService> imageService,
      const ResolvedFile image
                                  );

  int loadImage(lua_State *L);
  int getImageWidth(lua_State *L);
  int getImageHeight(lua_State *L);
  int resizeImage(lua_State *L);
  int cropImage(lua_State *L);
  int writeImage(lua_State *L);
};
