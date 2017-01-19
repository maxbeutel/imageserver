#include <utility>

#include <gtest/gtest.h>

#include "imageserver/image/ImageService.hpp"
#include "imageserver/image/ImageFilterService.hpp"

std::string TESTS_DIRECTORY = "";
const std::string TEST_IMAGE_FILE_NAME("sample-image.png");

TEST(ImageService, resizeImage)
{
  cv::Mat inputImage;
  inputImage = cv::imread(TESTS_DIRECTORY + "/fixtures/" + TEST_IMAGE_FILE_NAME);

  const ImageService imageService;
  imageService.resizeImage(inputImage, std::make_pair(100, 100));
}

TEST(ImageService, cropImage)
{
  cv::Mat inputImage;
  inputImage = cv::imread(TESTS_DIRECTORY + "/fixtures/" + TEST_IMAGE_FILE_NAME);

  const ImageService imageService;
  imageService.cropImage(inputImage, std::make_pair(100, 100));
}

TEST(ImageFilterService, filterImage)
{
  auto configurationFileResult = ResolvedFile::resolveWithinBaseDirectory(
      TESTS_DIRECTORY + "/fixtures/",
      "dump.lua"
                                                                          );

  auto imageFileResult = ResolvedFile::resolveWithinBaseDirectory(
      TESTS_DIRECTORY + "/fixtures/",
      TEST_IMAGE_FILE_NAME
                                                                  );

  std::stringstream ss;

  ImageFilterService imageFilterService;
  imageFilterService.filterImage(configurationFileResult.first, imageFileResult.first, ss);

  std::string expectedOutput = "image width: 300.0, image height: 500.0";
  ASSERT_STREQ(expectedOutput.c_str(), ss.str().c_str());
}



// TEST(ImageProcessingConfigurationService, evaluateConfigurationFile_emptyParameters) {
//   std::map<std::string, std::string> parameters;
//   std::stringstream ss;

//   ImageProcessingConfigurationService configurationService;

//   auto configuration = configurationService.evaluateConfigurationFile(
//       TESTS_DIRECTORY + "/fixtures/dump-parameters.lua",
//       parameters,
//       ss
//                                                                       );
//   ASSERT_TRUE(ss.str().empty());
// }

GTEST_API_ int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);

  if (argc < 2) {
    std::cerr << "Usage: image_test <path to tests directory>" << std::endl;
    exit(1);
  }

  TESTS_DIRECTORY = std::string(argv[1]);

  return RUN_ALL_TESTS();
}
