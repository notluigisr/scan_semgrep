bool ber_read_OID_String(TALLOC_CTX *mem_ctx, DATA_BLOB blob, char **OID)
{
	size_t bytes_eaten;

	if (!_ber_read_OID_String_impl(mem_ctx, blob, OID, &bytes_eaten))
		return false;

	return (bytes_eaten == blob.length);
}