#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include <event2/keyvalq_struct.h>

#include "imageserver/server/ServerHelper.hpp"

std::pair<std::string, URI_TO_PATH_STATUS> uri_to_path(const char *uri) {
  assert(uri != NULL);

  struct evhttp_uri *decodedUri = NULL;
  const char *path = NULL;
  const char *decodedPath = NULL;

  URI_TO_PATH_STATUS status = URI_TO_PATH_STATUS::SUCCESS;

  decodedUri = evhttp_uri_parse(uri);

  if (!decodedUri) {
    status = URI_TO_PATH_STATUS::FAILURE_URI_PARSE;
    goto end;
  }

  path = evhttp_uri_get_path(decodedUri);

  if (!path) {
    status = URI_TO_PATH_STATUS::FAILURE_URI_TO_PATH;
    goto end;
  }

  decodedPath = evhttp_uridecode(path, 0, NULL);

  if (!decodedPath) {
    status = URI_TO_PATH_STATUS::FAILURE_PATH_DECODE;
    goto end;
  }

end:
  if (decodedUri) {
    evhttp_uri_free(decodedUri);
  }

  // @FIXME does path need to be free'ed when decodedPath fails?

  auto result = std::make_pair(
      (status == URI_TO_PATH_STATUS::SUCCESS ? std::string(decodedPath) : std::string("")),
      status
                         );

  free((void *)decodedPath);

  return result;
}

std::pair<std::string, bool> get_path_part_at(const std::string &path, const unsigned int index)
{
  std::stringstream ss;
  ss.str(path);

  std::string item;

  unsigned int i = 0;

  while (std::getline(ss, item, '/')) {
    if (item.empty()) {
      continue;
    }

    if (i == index) {
      return std::make_pair(item, true);
    }

    i++;
  }

  return std::make_pair("", false);
}
