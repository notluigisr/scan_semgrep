static inline int xrstor_state_booting(struct xsave_struct *fx, u64 mask)
{
	u32 lmask = mask;
	u32 hmask = mask >> 32;
	int err = 0;

	WARN_ON(system_state != SYSTEM_BOOTING);

	if (boot_cpu_has(X86_FEATURE_XSAVES))
		asm volatile("STR"
			"STR"
			: : "STR" (hmask)
			:   "STR");
	else
		asm volatile("STR"
			"STR"
			: : "STR" (hmask)
			:   "STR");

	asm volatile(xstate_fault
		     : "STR" (0)
		     : "STR");

	return err;
}