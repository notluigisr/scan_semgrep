int regset_tls_set(struct task_struct *target, const struct user_regset *regset,
		   unsigned int pos, unsigned int count,
		   const void *kbuf, const void __user *ubuf)
{
	struct user_desc infobuf[GDT_ENTRY_TLS_ENTRIES];
	const struct user_desc *info;

	if (pos >= GDT_ENTRY_TLS_ENTRIES * sizeof(struct user_desc) ||
	    (pos % sizeof(struct user_desc)) != 0 ||
	    (count % sizeof(struct user_desc)) != 0)
		return -EINVAL;

	if (kbuf)
		info = kbuf;
	else if (__copy_from_user(infobuf, ubuf, count))
		return -EFAULT;
	else
		info = infobuf;

	set_tls_desc(target,
		     GDT_ENTRY_TLS_MIN + (pos / sizeof(struct user_desc)),
		     info, count / sizeof(struct user_desc));

	return 0;
}