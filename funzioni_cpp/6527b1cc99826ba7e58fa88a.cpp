fingerprint_from_pk (PKT_public_key *pk, byte *array, size_t *ret_len)
{
  const byte *dp;
  size_t len;
  gcry_md_hd_t md;

  md = do_fingerprint_md(pk);
  dp = gcry_md_read( md, 0 );
  len = gcry_md_get_algo_dlen (gcry_md_get_algo (md));
  assert( len <= MAX_FINGERPRINT_LEN );
  if (!array)
    array = xmalloc ( len );
  memcpy (array, dp, len );
  pk->keyid[0] = buf32_to_u32 (dp+12);
  pk->keyid[1] = buf32_to_u32 (dp+16);
  gcry_md_close( md);

  if (ret_len)
    *ret_len = len;
  return array;
}