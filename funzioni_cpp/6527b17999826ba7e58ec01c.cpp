hugetlb_vmdelete_list(struct rb_root *root, pgoff_t start, pgoff_t end)
{
	struct vm_area_struct *vma;

	
	vma_interval_tree_foreach(vma, root, start, end ? end : ULONG_MAX) {
		unsigned long v_offset;

		
		if (vma->vm_pgoff < start)
			v_offset = (start - vma->vm_pgoff) << PAGE_SHIFT;
		else
			v_offset = 0;

		if (end) {
			end = ((end - start) << PAGE_SHIFT) +
			       vma->vm_start + v_offset;
			if (end > vma->vm_end)
				end = vma->vm_end;
		} else
			end = vma->vm_end;

		unmap_hugepage_range(vma, vma->vm_start + v_offset, end, NULL);
	}
}