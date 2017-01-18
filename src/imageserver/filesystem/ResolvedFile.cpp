#include <sstream>
#include <unistd.h>

#include "imageserver/filesystem/ResolvedFile.hpp"

ResolvedFile::ResolvedFile(const std::string fullPath)
    : fullPath{fullPath}
{
}

std::pair<ResolvedFile, RESOLVED_FILE_RESOLVE_STATUS> ResolvedFile::resolveWithinBaseDirectory(std::string baseDirectory, std::string fileName)
{
  std::stringstream ss;
  ss << baseDirectory << "/" << fileName;
  auto fullPath = ss.str();

  if (access(fullPath.c_str(), F_OK) == -1) {
    static ResolvedFile ResolvedFileNull("");
    return std::make_pair(ResolvedFileNull, RESOLVED_FILE_RESOLVE_STATUS::FAILURE_FILE_NOT_FOUND);
  }

  ResolvedFile resolvedFile(fullPath);
  return std::make_pair(std::move(resolvedFile), RESOLVED_FILE_RESOLVE_STATUS::SUCCESS);
}

std::string ResolvedFile::getFullPath() const
{
  return fullPath;
}
