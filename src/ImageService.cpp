#include "ImageService.hpp"

ImageService::ImageService()
{
}

void ImageService::processImage(std::unique_ptr<SourceImageFile> sourceImageFile) const
{
  // @FIXME load sourceImageFile here, pass to resize/etc. functions based on specifications
  // dump image again
  // resize/crop must be changed to have cv mat as first image (move them to lower level later?)
  // How to return a meaningful result to the caller? string? or object?
}

void ImageService::resizeImage(cv::Mat &inputImage, ImageSize imageSize) const
{
  cv::Mat outputImage;
  cv::Size outputImageSize(static_cast<int>(imageSize.first), static_cast<int>(imageSize.second));

  // @TODO when downsampling use INTER_CUBIC
  cv::resize(inputImage, outputImage, outputImageSize, cv::INTER_LINEAR);

  // @TODO that should be configurable
  // @TODO return result to the client
  // @TODO any exceptions that need to be captured?
  cv::imwrite("/tmp/imageserver-resized.png", outputImage); // @FIXME image extension should be kept!
}

void ImageService::cropImage(cv::Mat &inputImage, ImageSize imageSize) const
{
  // @TODO that should be configurable
  // @TODO return result to the client
  // @TODO any exceptions that need to be captured?
  cv::Rect ROI(0, 0, static_cast<int>(imageSize.first), static_cast<int>(imageSize.second));
  cv::Mat croppedImage = inputImage(ROI);

  cv::imwrite("/tmp/imageserver-cropped.png", croppedImage); // @FIXME image extension should be kept!
}
