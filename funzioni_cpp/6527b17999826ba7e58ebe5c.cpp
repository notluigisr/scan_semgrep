static int ext4_end_io_nolock(ext4_io_end_t *io)
{
	struct inode *inode = io->inode;
	loff_t offset = io->offset;
	ssize_t size = io->size;
	int ret = 0;

	ext4_debug("STR"
		   "STR",
	           io, inode->i_ino, io->list.next, io->list.prev);

	if (list_empty(&io->list))
		return ret;

	if (io->flag != EXT4_IO_UNWRITTEN)
		return ret;

	if (offset + size <= i_size_read(inode))
		ret = ext4_convert_unwritten_extents(inode, offset, size);

	if (ret < 0) {
		printk(KERN_EMERG "STR"
			"STR"
			"STR",
                       __func__, ret, inode->i_ino);
		return ret;
	}

	
	io->flag = 0;
	return ret;
}