#include <utility>

#include "gtest/gtest.h"

#include "ImageService.hpp"
#include "SourceImageFile.hpp"

std::string TESTS_DIRECTORY = "";
const std::string TEST_IMAGE_FILE_NAME("sample-image.png");

TEST(SourceImageFile, resolveWithinBaseDirectory) {
  auto sourceImageFileResult = SourceImageFile::resolveWithinBaseDirectory(TESTS_DIRECTORY + "/fixtures", TEST_IMAGE_FILE_NAME);

  const auto sourceImageFile = std::move(sourceImageFileResult.first);
  const auto status = sourceImageFileResult.second;

  ASSERT_EQ(SOURCE_IMAGE_FILE_RESOLVE_STATUS::SUCCESS, status);
  ASSERT_STREQ(sourceImageFile->getFullPath().c_str(), std::string(TESTS_DIRECTORY + "/fixtures/" + TEST_IMAGE_FILE_NAME).c_str());
}

TEST(SourceImageFile, resolveWithinBaseDirectory_fileNotFound) {
  auto sourceImageFileResult = SourceImageFile::resolveWithinBaseDirectory(TESTS_DIRECTORY + "/fixtures", "not-there.bmp");

  const auto sourceImageFile = std::move(sourceImageFileResult.first);
  const auto status = sourceImageFileResult.second;

  ASSERT_EQ(SOURCE_IMAGE_FILE_RESOLVE_STATUS::FAILURE_FILE_NOT_FOUND, status);
}

TEST(SourceImageFile, readContents) {
  auto sourceImageFileResult = SourceImageFile::resolveWithinBaseDirectory(TESTS_DIRECTORY + "/fixtures", TEST_IMAGE_FILE_NAME);

  auto sourceImageFile = std::move(sourceImageFileResult.first);
  auto contents = sourceImageFile->readContents();

  ASSERT_EQ(static_cast<std::vector<char>::size_type>(4515), contents.size());
}

TEST(ImageService, resizeImage) {
  auto sourceImageFileResult = SourceImageFile::resolveWithinBaseDirectory(TESTS_DIRECTORY + "/fixtures", TEST_IMAGE_FILE_NAME);

  const ImageService imageService;

  imageService.resizeImage(
      std::move(sourceImageFileResult.first),
      std::make_pair(100, 100)
                                         );
}

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  if (argc < 2) {
    std::cerr << "Usage: image_test <path to tests directory>" << std::endl;
    exit(1);
  }

  TESTS_DIRECTORY = std::string(argv[1]);

  return RUN_ALL_TESTS();
}
