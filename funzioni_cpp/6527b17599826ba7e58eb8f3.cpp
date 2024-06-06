int nfs_updatepage(struct file *file, struct page *page,
		unsigned int offset, unsigned int count)
{
	struct nfs_open_context *ctx = nfs_file_open_context(file);
	struct inode	*inode = page_file_mapping(page)->host;
	int		status = 0;

	nfs_inc_stats(inode, NFSIOS_VFSUPDATEPAGE);

	dprintk("STR",
		file->f_path.dentry->d_parent->d_name.name,
		file->f_path.dentry->d_name.name, count,
		(long long)(page_file_offset(page) + offset));

	
	if (nfs_write_pageuptodate(page, inode) &&
			inode->i_flock == NULL &&
			!(file->f_flags & O_DSYNC)) {
		count = max(count + offset, nfs_page_length(page));
		offset = 0;
	}

	status = nfs_writepage_setup(ctx, page, offset, count);
	if (status < 0)
		nfs_set_pageerror(page);
	else
		__set_page_dirty_nobuffers(page);

	dprintk("STR",
			status, (long long)i_size_read(inode));
	return status;
}