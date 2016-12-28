#pragma once

#include <string>
#include <memory>
#include <utility>
#include <cstdint>

enum class SOURCE_IMAGE_FILE_RESOLVE_STATUS : std::int8_t {
  SUCCESS = 0,
  FAILURE_FILE_NOT_FOUND,
};

class SourceImageFile {
 public:
  std::string getFullPath() const;
  static std::pair<std::unique_ptr<SourceImageFile>, SOURCE_IMAGE_FILE_RESOLVE_STATUS> resolveWithinBaseDirectory(std::string baseDirectory, std::string fileName);

 private:
  const std::string fullPath;

  explicit SourceImageFile(std::string fullPath);
};
