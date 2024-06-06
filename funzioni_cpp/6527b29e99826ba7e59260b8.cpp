static int efi_capsule_release(struct inode *inode, struct file *file)
{
	struct capsule_info *cap_info = file->private_data;

	if (cap_info->index > 0 &&
	    (cap_info->header.headersize == 0 ||
	     cap_info->count < cap_info->total_size)) {
		pr_err("STR");
		efi_free_all_buff_pages(cap_info);
	}

	kfree(cap_info->pages);
	kfree(cap_info->phys);
	kfree(file->private_data);
	file->private_data = NULL;
	return 0;
}