Curl_ssl_connect(struct Curl_easy *data, struct connectdata *conn,
                 int sockindex)
{
  CURLcode result;

#ifndef CURL_DISABLE_PROXY
  if(conn->bits.proxy_ssl_connected[sockindex]) {
    result = ssl_connect_init_proxy(conn, sockindex);
    if(result)
      return result;
  }
#endif

  if(!ssl_prefs_check(data))
    return CURLE_SSL_CONNECT_ERROR;

  
  conn->ssl[sockindex].use = TRUE;
  conn->ssl[sockindex].state = ssl_connection_negotiating;

  result = Curl_ssl->connect_blocking(data, conn, sockindex);

  if(!result)
    Curl_pgrsTime(data, TIMER_APPCONNECT); 
  else
    conn->ssl[sockindex].use = FALSE;

  return result;
}