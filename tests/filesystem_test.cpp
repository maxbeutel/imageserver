#include <utility>

#include <gtest/gtest.h>

#include "imageserver/filesystem/ResolvedFile.hpp"

std::string TESTS_DIRECTORY = "";
const std::string TEST_IMAGE_FILE_NAME("sample-image.png");

TEST(ResolvedFile, resolveWithinBaseDirectory) {
  auto sourceImageFileResult = ResolvedFile::resolveWithinBaseDirectory(TESTS_DIRECTORY + "/fixtures", TEST_IMAGE_FILE_NAME);

  const auto sourceImageFile = std::move(sourceImageFileResult.first);
  const auto status = sourceImageFileResult.second;

  ASSERT_EQ(RESOLVED_FILE_RESOLVE_STATUS::SUCCESS, status);
  ASSERT_STREQ(sourceImageFile.getFullPath().c_str(), std::string(TESTS_DIRECTORY + "/fixtures/" + TEST_IMAGE_FILE_NAME).c_str());
}

TEST(ResolvedFile, resolveWithinBaseDirectory_fileNotFound) {
  auto sourceImageFileResult = ResolvedFile::resolveWithinBaseDirectory(TESTS_DIRECTORY + "/fixtures", "not-there.bmp");

  const auto sourceImageFile = std::move(sourceImageFileResult.first);
  const auto status = sourceImageFileResult.second;

  ASSERT_EQ(RESOLVED_FILE_RESOLVE_STATUS::FAILURE_FILE_NOT_FOUND, status);
}

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  if (argc < 2) {
    std::cerr << "Usage: filesystem_test <path to tests directory>" << std::endl;
    exit(1);
  }

  TESTS_DIRECTORY = std::string(argv[1]);

  return RUN_ALL_TESTS();
}
