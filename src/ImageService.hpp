#pragma once

#include <memory>
#include <utility>

#include "SourceImageFile.hpp"

typedef std::pair<unsigned int, unsigned int> ImageSize;

class ImageService {
 public:
  ImageService();
  void resizeImage(std::unique_ptr<SourceImageFile> sourceImageFile, ImageSize imageSize) const;
  void cropImage(std::unique_ptr<SourceImageFile> sourceImageFile, ImageSize imageSize) const;
};
