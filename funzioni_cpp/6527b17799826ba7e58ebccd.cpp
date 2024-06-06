void safe_connect(MYSQL* mysql, const char *name, const char *host,
                  const char *user, const char *pass, const char *db,
                  int port, const char *sock)
{
  int failed_attempts= 0;

  DBUG_ENTER("STR");

  verbose_msg("STR"
              "STR", 
              host, port, sock, user, name, failed_attempts);
  while(!mysql_real_connect(mysql, host,user, pass, db, port, sock,
                            CLIENT_MULTI_STATEMENTS | CLIENT_REMEMBER_OPTIONS))
  {
    

    if ((mysql_errno(mysql) == CR_CONN_HOST_ERROR ||
         mysql_errno(mysql) == CR_CONNECTION_ERROR) &&
        failed_attempts < opt_max_connect_retries)
    {
      verbose_msg("STR", failed_attempts,
                  opt_max_connect_retries, mysql_errno(mysql),
                  mysql_error(mysql));
      my_sleep(connection_retry_sleep);
    }
    else
    {
      if (failed_attempts > 0)
        die("STR", name,
            failed_attempts, mysql_errno(mysql), mysql_error(mysql));
      else
        die("STR", name,
            mysql_errno(mysql), mysql_error(mysql));
    }
    failed_attempts++;
  }
  verbose_msg("STR");
  DBUG_VOID_RETURN;
}