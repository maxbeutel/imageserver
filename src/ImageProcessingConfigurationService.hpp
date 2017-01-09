#pragma once

#include <map>
#include <memory>
#include <string>

#include "EvaluatedImageProcessingConfiguration.hpp"

class ImageProcessingConfigurationService {
 public:
  ImageProcessingConfigurationService();
  std::unique_ptr<EvaluatedImageProcessingConfiguration> evaluateConfigurationFile(
      const std::string configurationFileFullPath,
      const std::map<std::string, std::string> &parameters
                                                                                   ) const;
};
