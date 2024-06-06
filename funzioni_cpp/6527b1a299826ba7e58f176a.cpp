nautilus_file_is_directory (NautilusFile *file)
{
	return nautilus_file_get_file_type (file) == G_FILE_TYPE_DIRECTORY;
}