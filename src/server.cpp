#include <iostream>
#include <memory>

#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>

#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>

#include "ServerHelper.hpp"
#include "ImageService.hpp"

static void handle_file(struct evhttp_request *req, void *)
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
  assert(uriToPathResult.second == URI_TO_PATH_STATUS::SUCCESS);

  std::cout << "Got decoded path " << path << std::endl;

  //resolveWithinBaseDirectory
  // @FIXME this is very insecure code! Can inject any path
  // @FIXME double slashes occur when concatenating paths
  auto sourceImageFileResult = SourceImageFile::resolveWithinBaseDirectory("/tmp", path);

  if (sourceImageFileResult.second != SOURCE_IMAGE_FILE_RESOLVE_STATUS::SUCCESS) {
    std::cout << "File not found" << std::endl;

    evhttp_send_error(req, HTTP_NOTFOUND, 0);
    return;
  }

  auto sourceImageFile = std::move(sourceImageFileResult.first);

  std::cout << "Full path " << sourceImageFile->getFullPath() << std::endl;

  int fd = open(sourceImageFile->getFullPath().c_str(), O_RDONLY);
  assert(fd != -1);

  struct stat st;

  int s = fstat(fd, &st);
  assert(s == 0);

  const char *content_type = "image/png";

  evhttp_add_header(evhttp_request_get_output_headers(req), "X-Served-By", "imageserver");
  evhttp_add_header(evhttp_request_get_output_headers(req), "Content-Type", content_type);

  struct evbuffer *evb = NULL;
  evb = evbuffer_new();

  int addFileStatus = evbuffer_add_file(evb, fd, 0, st.st_size);

  if (addFileStatus == 0) {
    evhttp_send_reply(req, HTTP_OK, "OK", evb);
  } else {
    evhttp_send_reply(req, HTTP_INTERNAL, "Internal Server Error", evb);

    std::cout << "Failed to add file to event buffer" << std::endl;
  }

  if (evb) {
      evbuffer_free(evb);
  }
}

int main(int, char **argv)
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
