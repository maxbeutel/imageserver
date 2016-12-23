#pragma once

#include <memory>

#include "ImageRequest.hpp"

class ImageService {
 public:
  void cropImage(std::unique_ptr<ImageRequest> imageRequest) const;
};
