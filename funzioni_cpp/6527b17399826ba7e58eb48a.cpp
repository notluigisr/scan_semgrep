chansrv_cleanup(int pid)
{
  char text[256];

  g_snprintf(text, 255, "STR", pid);
  if (g_file_exist(text))
  {
    g_file_delete(text);
  }
  g_snprintf(text, 255, "STR", pid);
  if (g_file_exist(text))
  {
    g_file_delete(text);
  }
  return 0;
}