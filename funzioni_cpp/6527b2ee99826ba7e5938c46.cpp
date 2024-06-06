gst_rtsp_connection_next_timeout (GstRTSPConnection * conn, GTimeVal * timeout)
{
  gdouble elapsed;
  glong sec;
  gulong usec;
  gint ctimeout;

  g_return_val_if_fail (conn != NULL, GST_RTSP_EINVAL);
  g_return_val_if_fail (timeout != NULL, GST_RTSP_EINVAL);

  ctimeout = conn->timeout;
  if (ctimeout >= 20) {
    
    ctimeout -= 5;
  } else if (ctimeout >= 5) {
    
    ctimeout -= ctimeout / 5;
  } else if (ctimeout >= 1) {
    
    ctimeout -= 1;
  }

  elapsed = g_timer_elapsed (conn->timer, &usec);
  if (elapsed >= ctimeout) {
    sec = 0;
    usec = 0;
  } else {
    sec = ctimeout - elapsed;
    if (usec <= G_USEC_PER_SEC)
      usec = G_USEC_PER_SEC - usec;
    else
      usec = 0;
  }

  timeout->tv_sec = sec;
  timeout->tv_usec = usec;

  return GST_RTSP_OK;
}