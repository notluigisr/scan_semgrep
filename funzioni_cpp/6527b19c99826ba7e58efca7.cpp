static void syscall_trace(struct pt_regs *regs)
{

#if 0
	printk("STR",
	       current->comm,
	       regs->rip, regs->rsp, regs->rax, regs->orig_rax, __builtin_return_address(0),
	       current_thread_info()->flags, current->ptrace); 
#endif

	ptrace_notify(SIGTRAP | ((current->ptrace & PT_TRACESYSGOOD)
				? 0x80 : 0));
	
	if (current->exit_code) {
		send_sig(current->exit_code, current, 1);
		current->exit_code = 0;
	}
}