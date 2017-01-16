#include <sstream>
#include <unistd.h>

#include "imageserver/filesystem/ResolvedFile.hpp"

ResolvedFile::ResolvedFile(const std::string fullPath)
    : fullPath{fullPath}
{
}

std::pair<std::unique_ptr<ResolvedFile>, RESOLVED_FILE_RESOLVE_STATUS> ResolvedFile::resolveWithinBaseDirectory(std::string baseDirectory, std::string fileName)
{
  std::stringstream ss;
  ss << baseDirectory << "/" << fileName;
  auto fullPath = ss.str();

  if (access(fullPath.c_str(), F_OK) == -1) {
    return std::make_pair(std::unique_ptr<ResolvedFile>(nullptr), RESOLVED_FILE_RESOLVE_STATUS::FAILURE_FILE_NOT_FOUND);
  }

  return std::make_pair(std::unique_ptr<ResolvedFile>(new ResolvedFile(fullPath)), RESOLVED_FILE_RESOLVE_STATUS::SUCCESS);
}

std::string ResolvedFile::getFullPath() const
{
  return fullPath;
}