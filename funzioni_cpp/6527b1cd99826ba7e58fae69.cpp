idna_to_ascii_lz (const char *input, char **output, int flags)
{
  char *utf8;
  int rc;

  utf8 = stringprep_locale_to_utf8 (input);
  if (!utf8)
    return IDNA_ICONV_ERROR;

  rc = idna_to_ascii_8z (utf8, output, flags);

  free (utf8);

  return rc;
}