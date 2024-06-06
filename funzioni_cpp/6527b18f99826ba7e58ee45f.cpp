symbol_new (uniqstr tag, location loc)
{
  symbol *res = xmalloc (sizeof *res);
  uniqstr_assert (tag);

  
  if (tag[0] != '\"' && tag[0] != '\'' && strchr (tag, '-'))
    complain (&loc, Wyacc,
              _("STR"), tag);

  res->tag = tag;
  res->location = loc;
  res->translatable = false;
  res->location_of_lhs = false;
  res->alias = NULL;
  res->content = sym_content_new (res);
  res->is_alias = false;

  if (nsyms == SYMBOL_NUMBER_MAXIMUM)
    complain (NULL, fatal, _("STR"),
              SYMBOL_NUMBER_MAXIMUM);
  nsyms++;
  return res;
}