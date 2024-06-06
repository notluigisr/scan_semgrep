g_tcp_can_send(int sck, int millis)
{
  fd_set wfds;
  struct timeval time;
  int rv;

  time.tv_sec = millis / 1000;
  time.tv_usec = (millis * 1000) % 1000000;
  FD_ZERO(&wfds);
  if (sck > 0)
  {
    FD_SET(((unsigned int)sck), &wfds);
    rv = select(sck + 1, 0, &wfds, 0, &time);
    if (rv > 0)
    {
      return g_tcp_socket_ok(sck);
    }
  }
  return 0;
}