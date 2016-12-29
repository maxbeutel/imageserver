#include <iostream>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <signal.h>
#include <fcntl.h>

#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include <event2/keyvalq_struct.h>

#include "ServerHelper.hpp"

static void handle_file(struct evhttp_request *req, void *arg)
{
  const char *uri = evhttp_request_get_uri(req);

  // only GET requests allowed
  if (evhttp_request_get_command(req) != EVHTTP_REQ_GET) {
    evhttp_send_error(req, HTTP_BADREQUEST, 0);
    return;
  }

  std::cout << "GET " << uri << std::endl;

  auto uriToPathResult = uri_to_path(uri);

  auto path = uriToPathResult.first;
  auto status = uriToPathResult.second;
  assert(status == URI_TO_PATH_STATUS::SUCCESS && "Very optimistically only expecting successful parsing for now.");

  std::cout << "Got decoded path " << path << std::endl;

  evhttp_send_error(req, HTTP_NOTFOUND, 0);
}

int main(int argc, char **argv)
{
  struct event_base *base;
  struct evhttp *http;
  struct evhttp_bound_socket *handle;

  const ev_uint16_t port = 8881;
  const char *host = "0.0.0.0";

  base = event_base_new();

  if (!base) {
    std::cerr << "FAILURE: Couldn't create an event_base." << std::endl;
    return 1;
  }

  http = evhttp_new(base);

  if (!http) {
    std::cerr << "FAILURE: Couldn't create an evhttp." << std::endl;
    return 1;
  }

  // catchall handler
  evhttp_set_gencb(http, handle_file, argv[1]);

  handle = evhttp_bind_socket_with_handle(http, host, port);

  if (!handle) {
    std::cerr << "FAILURE: Couldn't bind to " << host << ":" << port << std::endl;
    return 1;
  }

  event_base_dispatch(base);

  return 0;
}
