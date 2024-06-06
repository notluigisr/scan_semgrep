				     bool poll_only)
	__must_hold(&ctx->completion_lock)
{
	struct hlist_head *list;
	struct io_kiocb *req;

	list = &ctx->cancel_hash[hash_long(sqe_addr, ctx->cancel_hash_bits)];
	hlist_for_each_entry(req, list, hash_node) {
		if (sqe_addr != req->user_data)
			continue;
		if (poll_only && req->opcode != IORING_OP_POLL_ADD)
			continue;
		return req;
	}
	return NULL;