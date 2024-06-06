void wsrep_plugins_post_init()
{
  THD *thd;
  I_List_iterator<THD> it(threads);

  while ((thd= it++))
  {
    if (IF_WSREP(thd->wsrep_applier,1))
    {
      
      ulonglong option_bits_saved= thd->variables.option_bits;

      plugin_thdvar_init(thd);

      
      thd->variables.option_bits= option_bits_saved;
    }
  }

  return;
}