#include <stdio.h>

#include "ServerHelper.hpp"
#include "ServerConfiguration.hpp"

#include "gtest/gtest.h"

TEST(uri_to_path, success) {
  auto result = uri_to_path("/foo/bar/");

  auto path = result.first;
  auto status = result.second;

  ASSERT_EQ(URI_TO_PATH_STATUS::SUCCESS, status);
  ASSERT_STREQ(path.c_str(), "/foo/bar/");
}

TEST(uri_to_path, uriAsEmptyStringFails) {
  auto result = uri_to_path(" ");

  auto path = result.first;
  auto status = result.second;

  ASSERT_EQ(URI_TO_PATH_STATUS::FAILURE_URI_PARSE, status);
  ASSERT_STREQ(path.c_str(), "");
}

TEST(uri_to_path, slashOnlySuccess) {
  auto result = uri_to_path("/");

  auto path = result.first;
  auto status = result.second;

  ASSERT_EQ(URI_TO_PATH_STATUS::SUCCESS, status);
  ASSERT_STREQ(path.c_str(), "/");
}

TEST(get_path_part_at, pathAtIndexZero) {
  std::string path("/foo/bar/baz");

  auto result = get_path_part_at(path, 0);

  auto pathPart = result.first;
  auto status = result.second;

  ASSERT_TRUE(status);
  ASSERT_STREQ(pathPart.c_str(), "foo");
}

TEST(get_path_part_at, pathAtLastIndex) {
  std::string path("/foo/bar/baz");

  auto result = get_path_part_at(path, 2);

  auto pathPart = result.first;
  auto status = result.second;

  ASSERT_TRUE(status);
  ASSERT_STREQ(pathPart.c_str(), "baz");
}

TEST(get_path_part_at, pathAtIndex) {
  std::string path("/foo/bar/baz");

  auto result = get_path_part_at(path, 1);

  auto pathPart = result.first;
  auto status = result.second;

  ASSERT_TRUE(status);
  ASSERT_STREQ(pathPart.c_str(), "bar");
}

TEST(get_path_part_at, indexOutOfRange) {
  std::string path("/foo/bar/baz");

  auto result = get_path_part_at(path, 4);

  auto pathPart = result.first;
  auto status = result.second;

  ASSERT_FALSE(status);
}

TEST(parseServerConfigurationFromStdin, emptyInput)
{
  auto result = parseServerConfigurationFromStdin(0, NULL);
  auto errorMessages = result.second;

  ASSERT_EQ(static_cast<int>(errorMessages.size()), 1);
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
