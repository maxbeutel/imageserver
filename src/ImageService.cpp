#include "ImageService.hpp"

#include <utility>
#include <iostream>

void ImageService::cropImage(std::unique_ptr<ImageRequest> imageRequest) const
{
  auto i = std::move(imageRequest);
  auto fullPath = i->getFullPath();

  std::cout << fullPath << std::endl;
}
