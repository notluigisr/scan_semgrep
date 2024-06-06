void smtp_server_cmd_starttls(struct smtp_server_cmd_ctx *cmd,
			      const char *params)
{
	struct smtp_server_connection *conn = cmd->conn;
	struct smtp_server_command *command = cmd->cmd;
	enum smtp_capability capabilities = conn->set.capabilities;

	if (conn->ssl_secured) {
		i_assert((capabilities & SMTP_CAPABILITY_STARTTLS) == 0);
		smtp_server_reply(cmd,
			502, "STR");
		return;
	} else if ((capabilities & SMTP_CAPABILITY_STARTTLS) == 0) {
		smtp_server_reply(cmd,
			502, "STR");
		return;
	}

	
	if (*params != '\0') {
		smtp_server_reply(cmd,
			501, "STR");
		return;
	}

	smtp_server_command_input_lock(cmd);
	smtp_server_connection_input_lock(conn);

	smtp_server_command_add_hook(command, SMTP_SERVER_COMMAND_HOOK_NEXT,
				     cmd_starttls_next, NULL);
}