static void sendsuboption(struct Curl_easy *data, int option)
{
  ssize_t bytes_written;
  int err;
  unsigned short x, y;
  unsigned char *uc1, *uc2;
  struct TELNET *tn = data->req.p.telnet;
  struct connectdata *conn = data->conn;

  switch(option) {
  case CURL_TELOPT_NAWS:
    
    CURL_SB_CLEAR(tn);
    CURL_SB_ACCUM(tn, CURL_IAC);
    CURL_SB_ACCUM(tn, CURL_SB);
    CURL_SB_ACCUM(tn, CURL_TELOPT_NAWS);
    
    
    x = htons(tn->subopt_wsx);
    y = htons(tn->subopt_wsy);
    uc1 = (unsigned char *)&x;
    uc2 = (unsigned char *)&y;
    CURL_SB_ACCUM(tn, uc1[0]);
    CURL_SB_ACCUM(tn, uc1[1]);
    CURL_SB_ACCUM(tn, uc2[0]);
    CURL_SB_ACCUM(tn, uc2[1]);

    CURL_SB_ACCUM(tn, CURL_IAC);
    CURL_SB_ACCUM(tn, CURL_SE);
    CURL_SB_TERM(tn);
    

    printsub(data, '>', (unsigned char *)tn->subbuffer + 2,
             CURL_SB_LEN(tn)-2);

    
    bytes_written = swrite(conn->sock[FIRSTSOCKET], tn->subbuffer, 3);
    if(bytes_written < 0) {
      err = SOCKERRNO;
      failf(data, "STR", err);
    }
    
    send_telnet_data(data, (char *)tn->subbuffer + 3, 4);
    
    bytes_written = swrite(conn->sock[FIRSTSOCKET], tn->subbuffer + 7, 2);
    if(bytes_written < 0) {
      err = SOCKERRNO;
      failf(data, "STR", err);
    }
    break;
  }
}