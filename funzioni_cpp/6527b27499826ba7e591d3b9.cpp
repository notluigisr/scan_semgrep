static int data_pending(const struct Curl_easy *data)
{
  struct connectdata *conn = data->conn;

#ifdef ENABLE_QUIC
  if(conn->transport == TRNSPRT_QUIC)
    return Curl_quic_data_pending(data);
#endif

  
  return conn->handler->protocol&(CURLPROTO_SCP|CURLPROTO_SFTP) ||
#if defined(USE_NGHTTP2)
    Curl_ssl_data_pending(conn, FIRSTSOCKET) ||
    
    ((conn->handler->protocol&PROTO_FAMILY_HTTP) && conn->httpversion >= 20);
#else
    Curl_ssl_data_pending(conn, FIRSTSOCKET);
#endif
}