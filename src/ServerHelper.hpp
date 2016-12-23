#pragma once

#include <string>
#include <tuple>
#include <cstdint>

enum class URI_TO_PATH_STATUS : std::int8_t {
  SUCCESS = 0,
  FAILURE_URI_PARSE,
  FAILURE_URI_TO_PATH,
  FAILURE_PATH_DECODE,
};

std::tuple<std::string, URI_TO_PATH_STATUS> uri_to_path(const char *uri);
