#include <stdio.h>

#include "gtest/gtest.h"

#include "ImageService.hpp"
#include "ImageRequest.hpp"

const std::string directoryPath("/tmp");
const std::string imageName("file.png");

TEST(ImageRequest, Constructor) {
  const ImageRequest imageRequest(directoryPath, imageName);
  auto fullPath = imageRequest.getFullPath();

  ASSERT_STREQ(fullPath.c_str(), "/tmp/file.png");
}

TEST(ImageService, cropImage) {
  const std::string expectedFullPath = "/tmp/file.png";

  ImageService imageService;

  imageService.cropImage(
      std::unique_ptr<ImageRequest>(new ImageRequest(directoryPath, imageName))
                         );
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
