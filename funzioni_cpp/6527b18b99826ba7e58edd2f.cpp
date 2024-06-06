xt_replace_table(struct xt_table *table,
	      unsigned int num_counters,
	      struct xt_table_info *newinfo,
	      int *error)
{
	struct xt_table_info *private;
	unsigned int cpu;
	int ret;

	ret = xt_jumpstack_alloc(newinfo);
	if (ret < 0) {
		*error = ret;
		return NULL;
	}

	
	local_bh_disable();
	private = table->private;

	
	if (num_counters != private->number) {
		pr_debug("STR",
			 num_counters, private->number);
		local_bh_enable();
		*error = -EAGAIN;
		return NULL;
	}

	newinfo->initial_entries = private->initial_entries;
	
	smp_wmb();
	table->private = newinfo;

	
	smp_wmb();

	
	local_bh_enable();

	
	for_each_possible_cpu(cpu) {
		seqcount_t *s = &per_cpu(xt_recseq, cpu);
		u32 seq = raw_read_seqcount(s);

		if (seq & 1) {
			do {
				cond_resched();
				cpu_relax();
			} while (seq == raw_read_seqcount(s));
		}
	}

	audit_log_nfcfg(table->name, table->af, private->number,
			!private->number ? AUDIT_XT_OP_REGISTER :
					   AUDIT_XT_OP_REPLACE,
			GFP_KERNEL);
	return private;
}