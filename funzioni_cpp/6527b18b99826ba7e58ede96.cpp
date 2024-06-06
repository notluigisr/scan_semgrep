static inline int compat_copy_match_from_user(struct ipt_entry_match *m,
	void **dstptr, compat_uint_t *size, const char *name,
	const struct ipt_ip *ip, unsigned int hookmask, int *i)
{
	struct ipt_entry_match *dm;
	struct ipt_match *match;
	int ret;

	dm = (struct ipt_entry_match *)*dstptr;
	match = m->u.kernel.match;
	if (match->compat)
		match->compat(m, dstptr, size, COMPAT_FROM_USER);
	else
		xt_compat_match(m, dstptr, size, COMPAT_FROM_USER);

	ret = xt_check_match(match, AF_INET, dm->u.match_size - sizeof(*dm),
			     name, hookmask, ip->proto,
			     ip->invflags & IPT_INV_PROTO);
	if (ret)
		goto err;

	if (m->u.kernel.match->checkentry
	    && !m->u.kernel.match->checkentry(name, ip, match, dm->data,
					      hookmask)) {
		duprintf("STR",
			 m->u.kernel.match->name);
		ret = -EINVAL;
		goto err;
	}
	(*i)++;
	return 0;

err:
	module_put(m->u.kernel.match->me);
	return ret;
}