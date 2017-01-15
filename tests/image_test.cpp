#include <utility>

#include <gtest/gtest.h>

#include "imageserver/image/ImageService.hpp"
#include "imageserver/image/SourceImageFile.hpp"
#include "imageserver/image/ImageProcessingConfigurationService.hpp"

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

TEST(ImageService, processImage) {
  auto sourceImageFileResult = SourceImageFile::resolveWithinBaseDirectory(TESTS_DIRECTORY + "/fixtures", TEST_IMAGE_FILE_NAME);

  const ImageService imageService;
  imageService.processImage(std::move(sourceImageFileResult.first), "/tmp/test.png");
}

TEST(ImageService, resizeImage) {
  cv::Mat inputImage;
  inputImage = cv::imread(TESTS_DIRECTORY + "/fixtures/" + TEST_IMAGE_FILE_NAME);

  const ImageService imageService;
  imageService.resizeImage(inputImage, std::make_pair(100, 100));
}

TEST(ImageService, cropImage) {
  cv::Mat inputImage;
  inputImage = cv::imread(TESTS_DIRECTORY + "/fixtures/" + TEST_IMAGE_FILE_NAME);

  const ImageService imageService;
  imageService.cropImage(inputImage, std::make_pair(100, 100));
}

TEST(ImageProcessingConfigurationService, evaluateConfigurationFile_dumpingParameters) {
  std::map<std::string, std::string> parameters = { {"param1", "value1"}, { "param2", "12345" } };
  std::stringstream ss;

  ImageProcessingConfigurationService configurationService;

  auto configuration = configurationService.evaluateConfigurationFile(
      "/tmp/bla.lua",
      parameters,
      ss
                                                                      );
  ASSERT_STREQ("param1: value1, param2: 12345", ss.str().c_str());
}

TEST(ImageProcessingConfigurationService, evaluateConfigurationFile_emptyParameters) {
  std::map<std::string, std::string> parameters;
  std::stringstream ss;

  ImageProcessingConfigurationService configurationService;

  auto configuration = configurationService.evaluateConfigurationFile(
      "/tmp/bla.lua",
      parameters,
      ss
                                                                      );
  ASSERT_TRUE(ss.str().empty());
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
