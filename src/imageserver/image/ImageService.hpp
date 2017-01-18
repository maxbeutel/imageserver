#pragma once

#include <memory>
#include <utility>

#include <opencv2/opencv.hpp>

#include "imageserver/filesystem/ResolvedFile.hpp"

typedef std::pair<unsigned int, unsigned int> ImageSize;

class ImageService {
 public:
  ImageService();

  ImageSize getImageSize(const cv::Mat &inputImage) const;
  cv::Mat loadImage(const ResolvedFile &imageFile) const;
  void resizeImage(cv::Mat &inputImage, const ImageSize imageSize) const;
  void cropImage(cv::Mat &inputImage, const ImageSize imageSize) const;
};
