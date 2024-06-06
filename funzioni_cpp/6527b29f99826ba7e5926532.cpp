int mnt_update_set_filename(struct libmnt_update *upd, const char *filename,
			    int userspace_only)
{
	const char *path = NULL;
	int rw = 0;

	assert(upd);

	
	if (filename) {
		char *p = strdup(filename);
		if (!p)
			return -ENOMEM;

		upd->userspace_only = userspace_only;
		free(upd->filename);
		upd->filename = p;
	}

	if (upd->filename)
		return 0;

	
	mnt_has_regular_mtab(&path, &rw);
	if (!rw) {
		path = NULL;
		mnt_has_regular_utab(&path, &rw);
		if (!rw)
			return -EACCES;
		upd->userspace_only = TRUE;
	}
	upd->filename = strdup(path);
	if (!upd->filename)
		return -ENOMEM;

	return 0;
}