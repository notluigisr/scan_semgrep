const char *module_address_lookup(unsigned long addr,
			    unsigned long *size,
			    unsigned long *offset,
			    char **modname,
			    char *namebuf)
{
	const char *ret = NULL;
	struct module *mod;

	preempt_disable();
	mod = __module_address(addr);
	if (mod) {
		if (modname)
			*modname = mod->name;

		ret = find_kallsyms_symbol(mod, addr, size, offset);
	}
	
	if (ret) {
		strncpy(namebuf, ret, KSYM_NAME_LEN - 1);
		ret = namebuf;
	}
	preempt_enable();

	return ret;
}