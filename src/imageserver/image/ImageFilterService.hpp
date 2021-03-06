#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <cstdint>

#include "imageserver/filesystem/ResolvedFile.hpp"

enum class FILTER_IMAGE_STATUS : std::int8_t {
  SUCCESS = 0,
};

// @TODO merge ImageService and ImageFilterService?
class ImageFilterService {
 public:
  ImageFilterService();

  // @TODO return some result (so that bytes of the result image can be read)
  FILTER_IMAGE_STATUS filterImage(
      const ResolvedFile &configurationFile,
      const ResolvedFile &image,
      std::ostream &configurationFileOutputStream
                   ) const;
};
