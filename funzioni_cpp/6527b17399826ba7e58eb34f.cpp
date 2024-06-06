ephy_embed_single_initialize (EphyEmbedSingle *single)
{
  SoupSession *session;
  SoupCookieJar *jar;
  char *filename;
  char *cookie_policy;

  
  if (g_file_test (NSPLUGINWRAPPER_SETUP, G_FILE_TEST_EXISTS) != FALSE)
    g_spawn_command_line_sync (NSPLUGINWRAPPER_SETUP, NULL, NULL, NULL, NULL);

  ephy_embed_prefs_init ();

  session = webkit_get_default_session ();

  
  filename = g_build_filename (ephy_dot_dir (), "STR", NULL);
  jar = soup_cookie_jar_sqlite_new (filename, FALSE);
  g_free (filename);
  cookie_policy = eel_gconf_get_string (CONF_SECURITY_COOKIES_ACCEPT);
  ephy_embed_prefs_set_cookie_jar_policy (jar, cookie_policy);
  g_free (cookie_policy);

  soup_session_add_feature (session, SOUP_SESSION_FEATURE (jar));
  g_object_unref (jar);

  
  soup_session_add_feature_by_type (session, SOUP_TYPE_PROXY_RESOLVER_GNOME);

#ifdef SOUP_TYPE_PASSWORD_MANAGER
  
  if (ephy_has_private_profile () == FALSE)
    soup_session_add_feature_by_type (session, SOUP_TYPE_PASSWORD_MANAGER_GNOME);
#endif

  return TRUE;
}