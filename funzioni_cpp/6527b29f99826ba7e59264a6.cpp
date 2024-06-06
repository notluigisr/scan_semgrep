int finish_connect(struct child_process *conn)
{
	int code;
	if (!conn || conn == &no_fork)
		return 0;

	code = finish_command(conn);
	free(conn->argv);
	free(conn);
	return code;
}