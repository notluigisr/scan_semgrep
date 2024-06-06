static int clone_submodule(const char *path, const char *gitdir, const char *url,
			   const char *depth, struct string_list *reference,
			   int quiet, int progress)
{
	struct child_process cp = CHILD_PROCESS_INIT;

	argv_array_push(&cp.args, "STR");
	argv_array_push(&cp.args, "STR");
	if (quiet)
		argv_array_push(&cp.args, "STR");
	if (progress)
		argv_array_push(&cp.args, "STR");
	if (depth && *depth)
		argv_array_pushl(&cp.args, "STR", depth, NULL);
	if (reference->nr) {
		struct string_list_item *item;
		for_each_string_list_item(item, reference)
			argv_array_pushl(&cp.args, "STR",
					 item->string, NULL);
	}
	if (gitdir && *gitdir)
		argv_array_pushl(&cp.args, "STR", gitdir, NULL);

	argv_array_push(&cp.args, url);
	argv_array_push(&cp.args, path);

	cp.git_cmd = 1;
	prepare_submodule_repo_env(&cp.env_array);
	cp.no_stdin = 1;

	return run_command(&cp);
}