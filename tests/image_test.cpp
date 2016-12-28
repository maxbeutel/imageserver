#include <utility>
#include <stdio.h>
#include <stdexcept>

#include "gtest/gtest.h"

#include "ImageService.hpp"
#include "SourceImageFile.hpp"

// @TODO make this fixtures
// @TODO this testsuite doesn't work with valgrind, it hangs
const std::string TEST_IMAGE_ABSOLUTE_PATH("/Users/max/Desktop/z1.jpg");
const std::string TEST_IMAGE_BASE_DIRECTORY("/Users/max/Desktop");
const std::string TEST_IMAGE_RELATIVE_PATH("z1.jpg");

TEST(SourceImageFile, resolveWithinBaseDirectory) {
  auto sourceImageFileResult = SourceImageFile::resolveWithinBaseDirectory(TEST_IMAGE_BASE_DIRECTORY, TEST_IMAGE_RELATIVE_PATH);

  const auto sourceImageFile = std::move(sourceImageFileResult.first);
  const auto status = sourceImageFileResult.second;

  ASSERT_EQ(SOURCE_IMAGE_FILE_RESOLVE_STATUS::SUCCESS, status);
  ASSERT_STREQ(sourceImageFile->getFullPath().c_str(), TEST_IMAGE_ABSOLUTE_PATH.c_str());
}

TEST(SourceImageFile, resolveWithinBaseDirectory_fileNotFound) {
  auto sourceImageFileResult = SourceImageFile::resolveWithinBaseDirectory(TEST_IMAGE_BASE_DIRECTORY, "not-there.bmp");

  const auto sourceImageFile = std::move(sourceImageFileResult.first);
  const auto status = sourceImageFileResult.second;

  ASSERT_EQ(SOURCE_IMAGE_FILE_RESOLVE_STATUS::FAILURE_FILE_NOT_FOUND, status);
}

TEST(ImageService, resizeImage) {
  auto sourceImageFileResult = SourceImageFile::resolveWithinBaseDirectory(TEST_IMAGE_BASE_DIRECTORY, TEST_IMAGE_RELATIVE_PATH);

  auto sourceImageFile = std::move(sourceImageFileResult.first);

  const ImageService imageService;

  imageService.resizeImage(
      std::move(sourceImageFileResult.first),
      std::make_pair(100, 100)
                                         );
}

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
