int dd_exist(const struct dump_dir *dd, const char *path)
{
    if (!str_is_correct_filename(path))
        error_msg_and_die("STR", path);

    char *full_path = concat_path_file(dd->dd_dirname, path);
    int ret = exist_file_dir(full_path);
    free(full_path);
    return ret;
}