#include <stdio.h>

#include "ServerHelper.hpp"

#include "gtest/gtest.h"

TEST(uri_to_path, success) {
  auto result = uri_to_path("/foo/bar/");

  auto path = std::get<0>(result);
  auto status = std::get<1>(result);

  ASSERT_EQ(URI_TO_PATH_STATUS::SUCCESS, status);
  ASSERT_STREQ(path.c_str(), "/foo/bar/");
}

TEST(uri_to_path, uriAsEmptyStringFails) {
  auto result = uri_to_path(" ");

  auto path = std::get<0>(result);
  auto status = std::get<1>(result);

  ASSERT_EQ(URI_TO_PATH_STATUS::FAILURE_URI_PARSE, status);
  ASSERT_STREQ(path.c_str(), "");
}

TEST(uri_to_path, slashOnlySuccess) {
  auto result = uri_to_path("/");

  auto path = std::get<0>(result);
  auto status = std::get<1>(result);

  ASSERT_EQ(URI_TO_PATH_STATUS::SUCCESS, status);
  ASSERT_STREQ(path.c_str(), "/");
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
