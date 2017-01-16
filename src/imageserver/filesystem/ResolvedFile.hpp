#pragma once

#include <string>
#include <memory>
#include <utility>
#include <cstdint>
#include <vector>

enum class RESOLVED_FILE_RESOLVE_STATUS : std::int8_t {
  SUCCESS = 0,
  FAILURE_FILE_NOT_FOUND,
};

class ResolvedFile {
 public:
  static std::pair<std::unique_ptr<ResolvedFile>, RESOLVED_FILE_RESOLVE_STATUS> resolveWithinBaseDirectory(std::string baseDirectory, std::string fileName);

  std::string getFullPath() const;

 private:
  const std::string fullPath;

  explicit ResolvedFile(std::string fullPath);
};
