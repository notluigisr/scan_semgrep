static int selinux_socket_getpeersec_stream(struct socket *sock, char __user *optval,
					    int __user *optlen, unsigned len)
{
	int err = 0;
	char *scontext;
	u32 scontext_len;
	struct sk_security_struct *ssec;
	struct inode_security_struct *isec;
	u32 peer_sid = SECSID_NULL;

	isec = SOCK_INODE(sock)->i_security;

	if (isec->sclass == SECCLASS_UNIX_STREAM_SOCKET ||
	    isec->sclass == SECCLASS_TCP_SOCKET) {
		ssec = sock->sk->sk_security;
		peer_sid = ssec->peer_sid;
	}
	if (peer_sid == SECSID_NULL) {
		err = -ENOPROTOOPT;
		goto out;
	}

	err = security_sid_to_context(peer_sid, &scontext, &scontext_len);

	if (err)
		goto out;

	if (scontext_len > len) {
		err = -ERANGE;
		goto out_len;
	}

	if (copy_to_user(optval, scontext, scontext_len))
		err = -EFAULT;

out_len:
	if (put_user(scontext_len, optlen))
		err = -EFAULT;

	kfree(scontext);
out:
	return err;
}