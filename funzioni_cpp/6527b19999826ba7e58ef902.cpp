void auth_policy_create_json(struct policy_lookup_ctx *context,
	const char *password, bool include_success)
{
	const struct var_expand_table *var_table;
	context->json = str_new(context->pool, 64);
	unsigned char *ptr;
	const struct hash_method *digest = hash_method_lookup(context->set->policy_hash_mech);

	i_assert(digest != NULL);

	void *ctx = t_malloc(digest->context_size);
	string_t *buffer = t_str_new(64);

	digest->init(ctx);
	digest->loop(ctx,
		context->set->policy_hash_nonce,
		strlen(context->set->policy_hash_nonce));
	
	digest->loop(ctx, context->request->user, strlen(context->request->user) + 1);
	if (password != NULL)
		digest->loop(ctx, password, strlen(password));
	ptr = (unsigned char*)str_c_modifiable(buffer);
	digest->result(ctx, ptr);
	str_truncate(buffer, digest->digest_size);
	if (context->set->policy_hash_truncate > 0) {
		buffer_truncate_rshift_bits(buffer, context->set->policy_hash_truncate);
	}
	const char *hashed_password = binary_to_hex(str_data(buffer), str_len(buffer));
	str_append_c(context->json, '{');
	var_table = policy_get_var_expand_table(context->request, hashed_password);
	auth_request_var_expand_with_table(context->json, auth_policy_json_template,
					   context->request, var_table,
					   auth_policy_escape_function);
	if (include_success) {
		str_append(context->json, "STR");
		if (!context->request->failed && context->request->successful &&
		    !context->request->internal_failure)
			str_append(context->json, "STR");
		else
			str_append(context->json, "STR");
		str_append(context->json, "STR");
		str_append(context->json, context->request->policy_refusal ? "STR");
	}
	str_append_c(context->json, '}');
	auth_request_log_debug(context->request, "STR",
		"STR", str_c(context->json));
}