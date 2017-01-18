#pragma once

#include <memory>
#include <string>
#include <iostream>

#include "imageserver/filesystem/ResolvedFile.hpp"

// @TODO merge ImageService and ImageFilterService?
class ImageFilterService {
 public:
  ImageFilterService();

  // @TODO return some result (so that bytes of the result image can be read)
  void filterImage(
      const ResolvedFile &configurationFile,
      const ResolvedFile &image,
      std::ostream &configurationFileOutputStream
                   ) const;
};
