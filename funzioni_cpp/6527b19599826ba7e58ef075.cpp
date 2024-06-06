void altivec_unavailable_exception(struct pt_regs *regs)
{
#if !defined(CONFIG_ALTIVEC)
	if (user_mode(regs)) {
		
		_exception(SIGILL, regs, ILL_ILLOPC, regs->nip);
		return;
	}
#endif
	printk(KERN_EMERG "STR"
			"STR", regs->trap, regs->nip);
	die("STR", regs, SIGABRT);
}