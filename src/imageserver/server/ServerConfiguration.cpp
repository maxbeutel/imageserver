#include <unistd.h>

#include "imageserver/server/ServerConfiguration.hpp"

ServerConfiguration::ServerConfiguration()
{
}

void ServerConfiguration::setConfigurationFileBaseDirectory(const std::string configurationFileBaseDirectory)
{
  this->configurationFileBaseDirectory = configurationFileBaseDirectory;
}

std::string ServerConfiguration::getConfigurationFileBaseDirectory() const
{
  return configurationFileBaseDirectory;
}

void dumpErrorMessages(const std::vector<std::string> &errorMessages, std::ostream &outputStream)
{
  outputStream << "Usage: imageserver -c<path to filter config files>" << std::endl;

  for (auto errorMessage : errorMessages) {
    outputStream << errorMessage << std::endl;
  }
}

// @FIXME return readonly interface here
// @FIXME this is really fugly code
std::pair<std::unique_ptr<ServerConfiguration>, std::vector<std::string>> parseServerConfigurationFromStdin(int argc, char **argv)
{
  auto serverConfiguration = std::make_unique<ServerConfiguration>();
  std::vector<std::string> errorMessages;

  // disable default getopt error messages
  opterr = 0;
  int c = 0;

  if (argc == 0) {
    goto end;
  }

  // @NOTE: getopt is GPL
  while ((c = getopt(argc, argv, "c:")) != -1) {
    switch (c) {
      case 'c':
        serverConfiguration->setConfigurationFileBaseDirectory(std::string(optarg));

        break;

      case '?':
        if (optopt == 'c') {
          errorMessages.push_back("Option -c requires an argument.");
        } else {
          errorMessages.push_back("Unknown option character(s) given.");
        }

        break;

      default:

        break;
    }
  }

end:

  if (errorMessages.empty()) {
    return std::make_pair(std::move(serverConfiguration), errorMessages);
  }

  return std::make_pair(std::unique_ptr<ServerConfiguration>(nullptr), errorMessages);
}
