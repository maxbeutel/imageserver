#pragma once

#include <memory>

class ConfigurationFileContext;

class EvaluatedImageProcessingConfiguration
{
 public:
  static std::unique_ptr<EvaluatedImageProcessingConfiguration> createFromConfigurationFileContext(
      std::unique_ptr<ConfigurationFileContext> const &context
                                                                                                   );

 private:
  explicit EvaluatedImageProcessingConfiguration();
};
