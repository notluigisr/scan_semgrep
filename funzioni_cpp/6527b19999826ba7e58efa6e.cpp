static int cmd_starttls_start(struct smtp_server_connection *conn)
{
	const struct smtp_server_callbacks *callbacks = conn->callbacks;

	e_debug(conn->event, "STR");

	if (callbacks != NULL && callbacks->conn_start_tls != NULL) {
		struct smtp_server_connection *tmp_conn = conn;
		struct istream *input = conn->conn.input;
		struct ostream *output = conn->conn.output;
		int ret;

		smtp_server_connection_ref(tmp_conn);
		ret = callbacks->conn_start_tls(tmp_conn->context,
			&input, &output);
		if (!smtp_server_connection_unref(&tmp_conn) || ret < 0)
			return -1;

		smtp_server_connection_set_ssl_streams(conn, input, output);
	} else if (smtp_server_connection_ssl_init(conn) < 0) {
		smtp_server_connection_close(&conn,
			"STR");
		return -1;
	}

	
	smtp_server_connection_clear(conn);
	smtp_server_connection_input_unlock(conn);

	return 0;
}