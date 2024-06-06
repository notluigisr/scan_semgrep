static int u32_set_parms(struct net *net, struct tcf_proto *tp,
			 unsigned long base,
			 struct tc_u_knode *n, struct nlattr **tb,
			 struct nlattr *est, u32 flags, u32 fl_flags,
			 struct netlink_ext_ack *extack)
{
	int err;

	err = tcf_exts_validate_ex(net, tp, tb, est, &n->exts, flags,
				   fl_flags, extack);
	if (err < 0)
		return err;

	if (tb[TCA_U32_LINK]) {
		u32 handle = nla_get_u32(tb[TCA_U32_LINK]);
		struct tc_u_hnode *ht_down = NULL, *ht_old;

		if (TC_U32_KEY(handle)) {
			NL_SET_ERR_MSG_MOD(extack, "STR");
			return -EINVAL;
		}

		if (handle) {
			ht_down = u32_lookup_ht(tp->data, handle);

			if (!ht_down) {
				NL_SET_ERR_MSG_MOD(extack, "STR");
				return -EINVAL;
			}
			if (ht_down->is_root) {
				NL_SET_ERR_MSG_MOD(extack, "STR");
				return -EINVAL;
			}
			ht_down->refcnt++;
		}

		ht_old = rtnl_dereference(n->ht_down);
		rcu_assign_pointer(n->ht_down, ht_down);

		if (ht_old)
			ht_old->refcnt--;
	}
	if (tb[TCA_U32_CLASSID]) {
		n->res.classid = nla_get_u32(tb[TCA_U32_CLASSID]);
		tcf_bind_filter(tp, &n->res, base);
	}

	if (tb[TCA_U32_INDEV]) {
		int ret;
		ret = tcf_change_indev(net, tb[TCA_U32_INDEV], extack);
		if (ret < 0)
			return -EINVAL;
		n->ifindex = ret;
	}
	return 0;
}