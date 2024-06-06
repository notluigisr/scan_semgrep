
static int netdev_uevent(struct device *d, struct kobj_uevent_env *env)
{
	struct net_device *dev = to_net_dev(d);
	int retval;

	
	retval = add_uevent_var(env, "STR", dev->name);
	if (retval)
		goto exit;

	
	retval = add_uevent_var(env, "STR", dev->ifindex);

exit:
	return retval;