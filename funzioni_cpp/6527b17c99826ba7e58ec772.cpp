static int __videobuf_mmap_mapper(struct videobuf_queue *q,
			 struct vm_area_struct *vma)
{
	struct videbuf_vmalloc_memory *mem;
	struct videobuf_mapping *map;
	unsigned int first;
	int retval;
	unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;

	if (! (vma->vm_flags & VM_WRITE) || ! (vma->vm_flags & VM_SHARED))
		return -EINVAL;

	
	for (first = 0; first < VIDEO_MAX_FRAME; first++) {
		if (NULL == q->bufs[first])
			continue;

		if (V4L2_MEMORY_MMAP != q->bufs[first]->memory)
			continue;
		if (q->bufs[first]->boff == offset)
			break;
	}
	if (VIDEO_MAX_FRAME == first) {
		dprintk(1,"STR",
			(vma->vm_pgoff << PAGE_SHIFT));
		return -EINVAL;
	}

	
	map = q->bufs[first]->map = kmalloc(sizeof(struct videobuf_mapping),GFP_KERNEL);
	if (NULL == map)
		return -ENOMEM;

	map->start = vma->vm_start;
	map->end   = vma->vm_end;
	map->q     = q;

	q->bufs[first]->baddr = vma->vm_start;

	vma->vm_ops          = &videobuf_vm_ops;
	vma->vm_flags       |= VM_DONTEXPAND | VM_RESERVED;
	vma->vm_private_data = map;

	mem=q->bufs[first]->priv;
	BUG_ON (!mem);
	MAGIC_CHECK(mem->magic,MAGIC_VMAL_MEM);

	
	retval=remap_vmalloc_range(vma, mem->vmalloc,0);
	if (retval<0) {
		dprintk(1,"STR");

		mem->vma=kmalloc(sizeof(*vma),GFP_KERNEL);
		if (!mem->vma) {
			kfree(map);
			q->bufs[first]->map=NULL;
			return -ENOMEM;
		}
		memcpy(mem->vma,vma,sizeof(*vma));
	}

	dprintk(1,"STR",
		map,q,vma->vm_start,vma->vm_end,
		(long int) q->bufs[first]->bsize,
		vma->vm_pgoff,first);

	videobuf_vm_open(vma);

	return (0);
}