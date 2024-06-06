static int keyring_search_iterator(const void *object, void *iterator_data)
{
	struct keyring_search_context *ctx = iterator_data;
	const struct key *key = keyring_ptr_to_key(object);
	unsigned long kflags = key->flags;

	kenter("STR", key->serial);

	
	if (key->type != ctx->index_key.type) {
		kleave("STR");
		return 0;
	}

	
	if (ctx->flags & KEYRING_SEARCH_DO_STATE_CHECK) {
		if (kflags & ((1 << KEY_FLAG_INVALIDATED) |
			      (1 << KEY_FLAG_REVOKED))) {
			ctx->result = ERR_PTR(-EKEYREVOKED);
			kleave("STR", ctx->skipped_ret);
			goto skipped;
		}

		if (key->expiry && ctx->now.tv_sec >= key->expiry) {
			if (!(ctx->flags & KEYRING_SEARCH_SKIP_EXPIRED))
				ctx->result = ERR_PTR(-EKEYEXPIRED);
			kleave("STR", ctx->skipped_ret);
			goto skipped;
		}
	}

	
	if (!ctx->match_data.cmp(key, &ctx->match_data)) {
		kleave("STR");
		return 0;
	}

	
	if (!(ctx->flags & KEYRING_SEARCH_NO_CHECK_PERM) &&
	    key_task_permission(make_key_ref(key, ctx->possessed),
				ctx->cred, KEY_NEED_SEARCH) < 0) {
		ctx->result = ERR_PTR(-EACCES);
		kleave("STR", ctx->skipped_ret);
		goto skipped;
	}

	if (ctx->flags & KEYRING_SEARCH_DO_STATE_CHECK) {
		
		if (kflags & (1 << KEY_FLAG_NEGATIVE)) {
			smp_rmb();
			ctx->result = ERR_PTR(key->reject_error);
			kleave("STR", ctx->skipped_ret);
			goto skipped;
		}
	}

	
	ctx->result = make_key_ref(key, ctx->possessed);
	kleave("STR");
	return 1;

skipped:
	return ctx->skipped_ret;
}