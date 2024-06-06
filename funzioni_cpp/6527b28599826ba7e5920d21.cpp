static int tab_is_tree(struct libmnt_table *tb)
{
	struct libmnt_fs *fs = NULL;
	struct libmnt_iter *itr;
	int rc = 0;

	itr = mnt_new_iter(MNT_ITER_BACKWARD);
	if (!itr)
		return 0;

	rc = (mnt_table_next_fs(tb, itr, &fs) == 0 &&
	      mnt_fs_is_kernel(fs) &&
	      mnt_fs_get_root(fs));

	mnt_free_iter(itr);
	return rc;
}