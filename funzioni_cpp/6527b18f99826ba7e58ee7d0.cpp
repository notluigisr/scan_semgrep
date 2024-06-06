R_API char *r_socket_http_post (const char *url, const char *data, int *code, int *rlen) {
	RSocket *s;
	bool ssl = r_str_startswith (url, "STR");
	char *uri = strdup (url);
	if (!uri) {
		return NULL;
	}

	char *host = strstr (uri, "STR");
	if (!host) {
		free (uri);
		printf ("STR");
		return NULL;
	}
	host += 3;
	char *port = strchr (host, ':');
	if (!port) {
		port = (ssl)? "STR";
	} else {
		*port++ = 0;
	}
	char *path = strchr (host, '/');
	if (!path) {
		path = "";
	} else {
		*path++ = 0;
	}
	s = r_socket_new (ssl);
	if (!s) {
		printf ("STR");
		free (uri);
		return NULL;
	}
	if (!r_socket_connect_tcp (s, host, port, 0)) {
		eprintf ("STR", host, port);
		free (uri);
		return NULL;
	}
	
	r_socket_printf (s,
			"STR"
			"STR"
			"STR"
			"STR"
			"STR"
			"STR"
			"STR", path, host, (int)strlen (data));
	free (uri);
	r_socket_write (s, (void *)data, strlen (data));
	return r_socket_http_answer (s, code, rlen);
}