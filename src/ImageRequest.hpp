#pragma once

#include <string>

class ImageRequest {
 public:
  ImageRequest(std::string directoryPath, std::string imageName);
  std::string getFullPath() const;

 private:
  const std::string directoryPath;
  const std::string imageName;
};
