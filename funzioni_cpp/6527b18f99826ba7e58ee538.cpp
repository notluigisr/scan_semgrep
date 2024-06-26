int verify_iovec(struct msghdr *m, struct iovec *iov, struct sockaddr_storage *address, int mode)
{
	int size, ct, err;

	if (m->msg_namelen) {
		if (mode == VERIFY_READ) {
			void __user *namep;
			namep = (void __user __force *) m->msg_name;
			err = move_addr_to_kernel(namep, m->msg_namelen,
						  address);
			if (err < 0)
				return err;
		}
		m->msg_name = address;
	} else {
		m->msg_name = NULL;
	}

	size = m->msg_iovlen * sizeof(struct iovec);
	if (copy_from_user(iov, (void __user __force *) m->msg_iov, size))
		return -EFAULT;

	m->msg_iov = iov;
	err = 0;

	for (ct = 0; ct < m->msg_iovlen; ct++) {
		size_t len = iov[ct].iov_len;

		if (len > INT_MAX - err) {
			len = INT_MAX - err;
			iov[ct].iov_len = len;
		}
		err += len;
	}

	return err;
}