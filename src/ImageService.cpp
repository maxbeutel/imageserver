#include "ImageService.hpp"

#include "opencv2/opencv.hpp"

ImageService::ImageService()
{
}

void ImageService::resizeImage(
    std::unique_ptr<SourceImageFile> sourceImageFile,
    ImageSize imageSize
                             ) const
{
  auto fullPath = sourceImageFile->getFullPath();

  cv::Mat inputImage;
  inputImage= cv::imread(fullPath);

  cv::Mat outputImage;
  cv::Size outputImageSize((int) imageSize.first, (int) imageSize.second);

  // @TODO when downsampling use INTER_CUBIC
  cv::resize(inputImage, outputImage, outputImageSize, cv::INTER_LINEAR);

  // @TODO that should be configurable
  // @TODO return result to the client
  // @TODO any exceptions that need to be captured?
  cv::imwrite("/tmp/frob.jpg", outputImage);
}
