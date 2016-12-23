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
#include <unistd.h>
#include <dirent.h>

#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include <event2/keyvalq_struct.h>

enum URI_TO_PATH_STATUS {
  EMPTY = -1,
  SUCCESS = 0,
  FAILURE_URI_PARSE,
  FAILURE_URI_TO_PATH,
  FAILURE_PATH_DECODE,
};

static std::string uri_to_path(const char *uri, URI_TO_PATH_STATUS *status) {
  assert(uri != NULL);
  assert(status != NULL);

  struct evhttp_uri *decodedUri = NULL;
  const char *path = NULL;
  const char *decodedPath = NULL;

  *status = SUCCESS;

  decodedUri = evhttp_uri_parse(uri);

  if (!decodedUri) {
    *status = FAILURE_URI_PARSE;
    goto end;
  }

  path = evhttp_uri_get_path(decodedUri);

  if (!path) {
    *status = FAILURE_URI_TO_PATH;
    goto end;
  }

  decodedPath = evhttp_uridecode(path, 0, NULL);

  if (!decodedPath) {
    *status = FAILURE_PATH_DECODE;
    goto end;
  }

end:
  if (decodedUri) {
    evhttp_uri_free(decodedUri);
  }

  // @FIXME does path need to be free'ed when decodedPath fails?

  if (*status != SUCCESS) {
    return std::string("");
  }

  return std::string(decodedPath);
}

static void handle_file(struct evhttp_request *req, void *arg)
{
  const char *uri = evhttp_request_get_uri(req);

  // only GET requests allowed
  if (evhttp_request_get_command(req) != EVHTTP_REQ_GET) {
    evhttp_send_error(req, HTTP_BADREQUEST, 0);
    return;
  }

  std::cout << "GET " << uri << std::endl;

  URI_TO_PATH_STATUS status = EMPTY;
  auto path = uri_to_path(uri, &status);
  assert(status == SUCCESS); // @FIXME could throw exception here, also check if string is empty!

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
