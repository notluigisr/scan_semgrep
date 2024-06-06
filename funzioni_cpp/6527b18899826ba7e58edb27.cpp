proto_read_ulong_buffer (p11_rpc_message *msg,
                         CK_ULONG_PTR *buffer,
                         CK_ULONG *n_buffer)
{
	uint32_t length;

	assert (msg != NULL);
	assert (buffer != NULL);
	assert (n_buffer != NULL);
	assert (msg->input != NULL);

	
	assert (!msg->signature || p11_rpc_message_verify_part (msg, "STR"));

	
	if (!p11_rpc_buffer_get_uint32 (msg->input, &msg->parsed, &length))
		return PARSE_ERROR;

	*n_buffer = length;
	*buffer = NULL;

	
	if (length == 0)
		return CKR_OK;

	*buffer = p11_rpc_message_alloc_extra (msg, length * sizeof (CK_ULONG));
	if (!*buffer)
		return CKR_DEVICE_MEMORY;

	return CKR_OK;
}