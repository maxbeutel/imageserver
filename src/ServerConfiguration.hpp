#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <memory>

class ServerConfiguration
{
 private:
  std::string configurationFileBaseDirectory;

 public:
  ServerConfiguration();

  void setConfigurationFileBaseDirectory(const std::string configurationFileBaseDirectory);
  std::string getConfigurationFileBaseDirectory() const;
};

void dumpErrorMessages(const std::vector<std::string> &errorMessages, std::ostream &outputStream);

std::pair<std::unique_ptr<ServerConfiguration>, std::vector<std::string>> parseServerConfigurationFromStdin(int argc, char **argv);
