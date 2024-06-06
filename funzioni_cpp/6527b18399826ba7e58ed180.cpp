static int hash__init_new_context(struct mm_struct *mm)
{
	int index;

	index = hash__alloc_context_id();
	if (index < 0)
		return index;

	
	if (mm->context.id == 0)
		slice_init_new_context_exec(mm);

	subpage_prot_init_new_context(mm);

	pkey_mm_init(mm);
	return index;
}