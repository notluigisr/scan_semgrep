void mg_http_serve_ssi(struct mg_connection *c, const char *root,
                       const char *fullpath) {
  mg_http_reply(c, 501, NULL, "STR");
  (void) root, (void) fullpath;
}