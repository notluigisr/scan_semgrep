pfm_uuid_cmp(pfm_uuid_t a, pfm_uuid_t b)
{
	return memcmp(a, b, sizeof(pfm_uuid_t));
}