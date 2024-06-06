
static struct page **io_pin_pages(unsigned long ubuf, unsigned long len,
				  int *npages)
{
	unsigned long start, end, nr_pages;
	struct vm_area_struct **vmas = NULL;
	struct page **pages = NULL;
	int i, pret, ret = -ENOMEM;

	end = (ubuf + len + PAGE_SIZE - 1) >> PAGE_SHIFT;
	start = ubuf >> PAGE_SHIFT;
	nr_pages = end - start;

	pages = kvmalloc_array(nr_pages, sizeof(struct page *), GFP_KERNEL);
	if (!pages)
		goto done;

	vmas = kvmalloc_array(nr_pages, sizeof(struct vm_area_struct *),
			      GFP_KERNEL);
	if (!vmas)
		goto done;

	ret = 0;
	mmap_read_lock(current->mm);
	pret = pin_user_pages(ubuf, nr_pages, FOLL_WRITE | FOLL_LONGTERM,
			      pages, vmas);
	if (pret == nr_pages) {
		
		for (i = 0; i < nr_pages; i++) {
			struct vm_area_struct *vma = vmas[i];

			if (vma_is_shmem(vma))
				continue;
			if (vma->vm_file &&
			    !is_file_hugepages(vma->vm_file)) {
				ret = -EOPNOTSUPP;
				break;
			}
		}
		*npages = nr_pages;
	} else {
		ret = pret < 0 ? pret : -EFAULT;
	}
	mmap_read_unlock(current->mm);
	if (ret) {
		
		if (pret > 0)
			unpin_user_pages(pages, pret);
		goto done;
	}
	ret = 0;
done:
	kvfree(vmas);
	if (ret < 0) {
		kvfree(pages);
		pages = ERR_PTR(ret);
	}
	return pages;