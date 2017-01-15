#pragma once

#include <memory>
#include <utility>

#include <opencv2/opencv.hpp>

#include "imageserver/image/SourceImageFile.hpp"

typedef std::pair<unsigned int, unsigned int> ImageSize;

class ImageService {
 public:
  ImageService();
  void processImage(const std::unique_ptr<SourceImageFile> sourceImageFile, const std::string outputFilePath) const;
  // @FIXME can Mat reference be const?
  void resizeImage(cv::Mat &inputImage, const ImageSize imageSize) const;
  void cropImage(cv::Mat &inputImage, const ImageSize imageSize) const;
};
