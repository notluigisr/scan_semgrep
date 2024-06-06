show_hidden_files_changed_callback (gpointer callback_data)
{
	show_hidden_files = eel_preferences_get_boolean (NAUTILUS_PREFERENCES_SHOW_HIDDEN_FILES);
}