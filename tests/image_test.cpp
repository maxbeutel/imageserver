#include <stdio.h>
#include <stdexcept>

#include "gtest/gtest.h"

#include "ImageService.hpp"
#include "SourceImageFile.hpp"

// @TODO make this fixtures
// @TODO this testsuite doesn't work with valgrind, it hangs
const std::string TEST_IMAGE_FULL_PATH("/Users/max/Desktop/z1.jpg");
const std::string TEST_IMAGE_BASE_DIRECTORY("/Users/max/Desktop");
const std::string TEST_IMAGE_PATH("z1.jpg");

// TEST(SourceImageFile, Constructor) {
//   const SourceImageFile sourceImageFile(TEST_IMAGE_FULL_PATH);

//   auto fullPath = sourceImageFile.getFullPath();
//   ASSERT_STREQ(fullPath.c_str(), TEST_IMAGE_FULL_PATH.c_str());
// }

// TEST(ImageService, resolvePathToSourceImageFile) {
//   const ImageService imageService;

//   auto sourceImageFileResult = imageService.resolvePathToSourceImageFile(
//       TEST_IMAGE_BASE_DIRECTORY,
//       TEST_IMAGE_PATH
//                                                                          );

//   ASSERT_TRUE(sourceImageFileResult);
// }

// TEST(ImageService, resolvePathToSourceImageFile_fileNotFound) {
//   const ImageService imageService;

//   auto sourceImageFileResult = imageService.resolvePathToSourceImageFile(
//       TEST_IMAGE_BASE_DIRECTORY,
//       "not-there.jpg"
//                                                                          );

//   ASSERT_FALSE(sourceImageFileResult);
// }

// TEST(ImageService, resizeImage) {
//   const ImageService imageService;

//   auto sourceImageFileResult = imageService.resolvePathToSourceImageFile(
//       TEST_IMAGE_BASE_DIRECTORY,
//       TEST_IMAGE_PATH
//                                                                          );

//   imageService.resizeImage(
//       std::move(sourceImageFileResult.value()),
//       std::make_tuple(100, 100)
//                                          );
// }

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
