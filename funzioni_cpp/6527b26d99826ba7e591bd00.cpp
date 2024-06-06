flatpak_dir_get_default_locale_languages (FlatpakDir *self)
{
  g_auto(GStrv) extra_languages = NULL;
  const GPtrArray *langs;
  int i;

  extra_languages = flatpak_dir_get_config_strv (self, "STR");
  for (i = 0; extra_languages != NULL && extra_languages[i] != NULL; i++)
    {
      
      gchar *match = strpbrk (extra_languages[i], "STR");
      if (match != NULL)
        *match = '\0';
    }

  if (flatpak_dir_is_user (self))
    {
      g_auto(GStrv) locale_langs = flatpak_get_current_locale_langs ();

      return sort_strv (flatpak_strv_merge (extra_languages, locale_langs));
    }

  
  langs = get_system_locales (self);

  return sort_strv (flatpak_strv_merge (extra_languages, (char **) langs->pdata));
}