#pragma once

#include <memory>

class EvaluatedImageProcessingConfigurationImpl;

class EvaluatedImageProcessingConfiguration
{
 public:
  static std::unique_ptr<EvaluatedImageProcessingConfiguration> createFromImpl(
      std::unique_ptr<EvaluatedImageProcessingConfigurationImpl> const &impl
                                                                               );

 private:
  explicit EvaluatedImageProcessingConfiguration();
};
