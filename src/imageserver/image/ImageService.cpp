#include "imageserver/image/ImageService.hpp"

ImageService::ImageService()
{
}

ImageSize ImageService::getImageSize(const cv::Mat &inputImage) const
{
  return {inputImage.size().width, inputImage.size().height};
}

cv::Mat ImageService::loadImage(const ResolvedFile &imageFile) const
{
  return cv::imread(imageFile.getFullPath().c_str());
}

void ImageService::resizeImage(cv::Mat &inputImage, const ImageSize imageSize) const
{
  cv::Mat outputImage;
  cv::Size outputImageSize(static_cast<int>(imageSize.first), static_cast<int>(imageSize.second));

  // @TODO when downsampling use INTER_CUBIC
  cv::resize(inputImage, inputImage, outputImageSize, cv::INTER_LINEAR);
}

void ImageService::cropImage(cv::Mat &inputImage, const ImageSize imageSize) const
{
  // @TODO that should be configurable
  // @TODO return result to the client
  // @TODO any exceptions that need to be captured?
  cv::Rect ROI(0, 0, static_cast<int>(imageSize.first), static_cast<int>(imageSize.second));
  inputImage(ROI);
}
