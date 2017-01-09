#include "EvaluatedImageProcessingConfiguration.hpp"


std::unique_ptr<EvaluatedImageProcessingConfiguration> EvaluatedImageProcessingConfiguration::createFromImpl(
    std::unique_ptr<EvaluatedImageProcessingConfigurationImpl> const &impl
                                                                                                                    )
{
  // NOTE: can't claim ownership of impl argument
  // @FIXME copy data over from impl to the configuration

  return std::unique_ptr<EvaluatedImageProcessingConfiguration>(new EvaluatedImageProcessingConfiguration());
}

EvaluatedImageProcessingConfiguration::EvaluatedImageProcessingConfiguration()
{
}
