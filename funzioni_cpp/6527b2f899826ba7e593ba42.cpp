bool SELECT_LEX_UNIT::set_lock_to_the_last_select(Lex_select_lock l)
{
  if (l.defined_lock)
  {
    SELECT_LEX *sel= first_select();
    while (sel->next_select())
      sel= sel->next_select();
    if (sel->braces)
    {
      my_error(ER_WRONG_USAGE, MYF(0), "STR",
               "STR");
      return TRUE;
    }
    l.set_to(sel);
  }
  return FALSE;
}