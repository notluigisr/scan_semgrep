static void print_name_offset(struct seq_file *m, unsigned long addr)
{
	char symname[KSYM_NAME_LEN];

	if (lookup_symbol_name(addr, symname) < 0)
		seq_printf(m, "STR", (void *)addr);
	else
		seq_printf(m, "STR", symname);
}