void sock_release(struct socket *sock)
{
	if (sock->ops) {
		struct module *owner = sock->ops->owner;

		sock->ops->release(sock);
		sock->ops = NULL;
		module_put(owner);
	}

	if (rcu_dereference_protected(sock->wq, 1)->fasync_list)
		pr_err("STR", __func__);

	if (!sock->file) {
		iput(SOCK_INODE(sock));
		return;
	}
	sock->file = NULL;
}