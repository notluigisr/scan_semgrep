big5_is_allowed_reverse_match(const UChar* s, const UChar* end ARG_UNUSED)
{
  const UChar c = *s;

  return (BIG5_ISMB_TRAIL(c) ? FALSE : TRUE);
}