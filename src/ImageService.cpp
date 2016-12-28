#include "ImageService.hpp"

#include "opencv2/opencv.hpp"

ImageService::ImageService()
{
}

void ImageService::resizeImage(std::unique_ptr<SourceImageFile> sourceImageFile, ImageSize imageSize) const
{
  auto fullPath = sourceImageFile->getFullPath();

  cv::Mat inputImage;
  inputImage = cv::imread(fullPath);

  cv::Mat outputImage;
  cv::Size outputImageSize(static_cast<int>(imageSize.first), static_cast<int>(imageSize.second));

  // @TODO when downsampling use INTER_CUBIC
  cv::resize(inputImage, outputImage, outputImageSize, cv::INTER_LINEAR);

  // @TODO that should be configurable
  // @TODO return result to the client
  // @TODO any exceptions that need to be captured?
  cv::imwrite("/tmp/imageserver-resized.png", outputImage); // @FIXME image extension should be kept!
}

void ImageService::cropImage(std::unique_ptr<SourceImageFile> sourceImageFile, ImageSize imageSize) const
{
  auto fullPath = sourceImageFile->getFullPath();

  cv::Mat inputImage;
  inputImage = cv::imread(fullPath);

  // cv::Mat outputImage;
  // cv::Size outputImageSize(static_cast<int>(imageSize.first), static_cast<int>(imageSize.second));

  // @TODO that should be configurable
  // @TODO return result to the client
  // @TODO any exceptions that need to be captured?
  cv::Rect ROI(0, 0, static_cast<int>(imageSize.first), static_cast<int>(imageSize.second));
  cv::Mat croppedImage = inputImage(ROI);

  cv::imwrite("/tmp/imageserver-cropped.png", croppedImage); // @FIXME image extension should be kept!
}
