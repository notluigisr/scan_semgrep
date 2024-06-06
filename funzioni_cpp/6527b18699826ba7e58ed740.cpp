GIT_INLINE(bool) verify_dotgit_ntfs(git_repository *repo, const char *path, size_t len)
{
	git_buf *reserved = git_repository__reserved_names_win32;
	size_t reserved_len = git_repository__reserved_names_win32_len;
	size_t start = 0, i;

	if (repo)
		git_repository__reserved_names(&reserved, &reserved_len, repo, true);

	for (i = 0; i < reserved_len; i++) {
		git_buf *r = &reserved[i];

		if (len >= r->size &&
			strncasecmp(path, r->ptr, r->size) == 0) {
			start = r->size;
			break;
		}
	}

	if (!start)
		return true;

	
	if (path[start] == '\\')
		return false;

	
	for (i = start; i < len; i++) {
		if (path[i] != ' ' && path[i] != '.')
			return true;
	}

	return false;
}