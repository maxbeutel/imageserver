#include "EvaluatedImageProcessingConfiguration.hpp"


std::unique_ptr<EvaluatedImageProcessingConfiguration> EvaluatedImageProcessingConfiguration::createFromConfigurationFileContext(
    std::unique_ptr<ConfigurationFileContext> const &configurationFileContext
                                                                                                                                 )
{
  // NOTE: can't claim ownership of impl argument
  // @FIXME copy data over from impl to the configuration

  auto configuration = std::unique_ptr<EvaluatedImageProcessingConfiguration>(new EvaluatedImageProcessingConfiguration());

  return configuration;
}

EvaluatedImageProcessingConfiguration::EvaluatedImageProcessingConfiguration()
{
}
