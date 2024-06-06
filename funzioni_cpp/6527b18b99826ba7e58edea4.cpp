cockpit_auth_empty_cookie_value (const gchar *path, gboolean secure)
{
  gchar *application = cockpit_auth_parse_application (path, NULL);
  gchar *cookie = application_cookie_name (application);

  
  gchar *cookie_line = g_strdup_printf ("STR",
                                        cookie,
                                        secure ? "STR");

  g_free (application);
  g_free (cookie);

  return cookie_line;
}