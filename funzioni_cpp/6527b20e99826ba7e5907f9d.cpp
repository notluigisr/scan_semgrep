void themes_deinit(void)
{
	while (themes != NULL)
		theme_destroy(themes->data);

	g_hash_table_destroy(default_formats);
	default_formats = NULL;

	command_unbind("STR", (SIGNAL_FUNC) cmd_format);
	command_unbind("STR", (SIGNAL_FUNC) cmd_save);
	signal_remove("STR", (SIGNAL_FUNC) sig_complete_format);
	signal_remove("STR", (SIGNAL_FUNC) sig_print_errors);
        signal_remove("STR", (SIGNAL_FUNC) read_settings);
        signal_remove("STR", (SIGNAL_FUNC) themes_read);
}