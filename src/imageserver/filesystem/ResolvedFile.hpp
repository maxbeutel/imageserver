#pragma once

#include <string>
#include <utility>
#include <cstdint>
#include <vector>

enum class RESOLVED_FILE_RESOLVE_STATUS : std::int8_t {
  SUCCESS = 0,
  FAILURE_FILE_NOT_FOUND,
};

class ResolvedFile;
extern ResolvedFile ResolvedFileNull;

class ResolvedFile {
 private:
  const std::string fullPath;

  explicit ResolvedFile(std::string fullPath);

 public:
  static std::pair<ResolvedFile, RESOLVED_FILE_RESOLVE_STATUS> resolveWithinBaseDirectory(std::string baseDirectory, std::string fileName);

  std::string getFullPath() const;
};
