#include <iostream>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <fstream>

#include "SourceImageFile.hpp"

SourceImageFile::SourceImageFile(const std::string fullPath)
    : fullPath{fullPath}
{
}

// @FIXME could move factory method to a file service or so, which then can be friend of this class
std::pair<std::unique_ptr<SourceImageFile>, SOURCE_IMAGE_FILE_RESOLVE_STATUS> SourceImageFile::resolveWithinBaseDirectory(std::string baseDirectory, std::string fileName)
{
  std::stringstream ss;
  ss << baseDirectory << "/" << fileName;
  auto fullPath = ss.str();

  if (access(fullPath.c_str(), F_OK) == -1) {
    return std::make_pair(std::unique_ptr<SourceImageFile>(nullptr), SOURCE_IMAGE_FILE_RESOLVE_STATUS::FAILURE_FILE_NOT_FOUND);
  }

  return std::make_pair(std::unique_ptr<SourceImageFile>(new SourceImageFile(fullPath)), SOURCE_IMAGE_FILE_RESOLVE_STATUS::SUCCESS);
}

std::string SourceImageFile::getFullPath() const
{
  return fullPath;
}

std::vector<char> SourceImageFile::readContents() const
{
  std::ifstream ifs(getFullPath(), std::ios::binary|std::ios::ate);
  auto pos = ifs.tellg();

  std::vector<char> result(pos);

  ifs.seekg(0, std::ios::beg);
  ifs.read(&result[0], pos);

  return result;
}
