#include <iostream>
#include <sstream>

#include "ImageRequest.hpp"

ImageRequest::ImageRequest(const std::string directoryPath, const std::string imageName)
    : directoryPath{directoryPath}, imageName{imageName}
{
}

std::string ImageRequest::getFullPath() const
{
  std::stringstream ss;
  ss << directoryPath << "/" << imageName;
  return ss.str();
}
