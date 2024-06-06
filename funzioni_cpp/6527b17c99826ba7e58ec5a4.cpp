static struct entry *alloc_entry(void)
{
	if (nr_entries >= MAX_ENTRIES)
		return NULL;

	return entries + nr_entries++;
}