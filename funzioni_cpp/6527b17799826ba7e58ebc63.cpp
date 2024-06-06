static void fix_hostname(struct SessionHandle *data,
                         struct connectdata *conn, struct hostname *host)
{
  size_t len;

#ifndef USE_LIBIDN
  (void)data;
  (void)conn;
#elif defined(CURL_DISABLE_VERBOSE_STRINGS)
  (void)conn;
#endif

  
  host->dispname = host->name;

  len = strlen(host->name);
  if(host->name[len-1] == '.')
    
    host->name[len-1]=0;

  if(!is_ASCII_name(host->name)) {
#ifdef USE_LIBIDN
  
  if(stringprep_check_version(LIBIDN_REQUIRED_VERSION)) {
    char *ace_hostname = NULL;
    int rc = idna_to_ascii_lz(host->name, &ace_hostname, 0);
    infof (data, "STR",
           stringprep_locale_charset ());
    if(rc != IDNA_SUCCESS)
      infof(data, "STR",
            host->name, Curl_idn_strerror(conn, rc));
    else {
      
      (void)tld_check_name(data, ace_hostname);

      host->encalloc = ace_hostname;
      
      host->name = host->encalloc;
    }
  }
#elif defined(USE_WIN32_IDN)
  
    char *ace_hostname = NULL;
    int rc = curl_win32_idn_to_ascii(host->name, &ace_hostname);
    if(rc == 0)
      infof(data, "STR",
            host->name);
    else {
      host->encalloc = ace_hostname;
      
      host->name = host->encalloc;
    }
#else
    infof(data, "STR");
#endif
  }
}