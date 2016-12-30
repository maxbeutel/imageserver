#pragma once

#include <memory>
#include <utility>
#include "opencv2/opencv.hpp"

#include "SourceImageFile.hpp"

typedef std::pair<unsigned int, unsigned int> ImageSize;

class ImageService {
 public:
  ImageService();
  void processImage(std::unique_ptr<SourceImageFile> sourceImageFile) const;
  void resizeImage(cv::Mat &inputImage, ImageSize imageSize) const;
  void cropImage(cv::Mat &inputImage, ImageSize imageSize) const;
};
