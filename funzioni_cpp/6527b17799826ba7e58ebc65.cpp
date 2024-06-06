CURLcode Curl_http_done(struct connectdata *conn,
                        CURLcode status, bool premature)
{
  struct SessionHandle *data = conn->data;
  struct HTTP *http =data->req.protop;

  Curl_unencode_cleanup(conn);

#ifdef USE_SPNEGO
  if(data->state.proxyneg.state == GSS_AUTHSENT ||
      data->state.negotiate.state == GSS_AUTHSENT)
    Curl_cleanup_negotiate(data);
#endif

  
  conn->fread_func = data->set.fread_func; 
  conn->fread_in = data->set.in; 
  conn->seek_func = data->set.seek_func; 
  conn->seek_client = data->set.seek_client; 

  if(http == NULL)
    return CURLE_OK;

  if(http->send_buffer) {
    Curl_send_buffer *buff = http->send_buffer;

    free(buff->buffer);
    free(buff);
    http->send_buffer = NULL; 
  }

  if(HTTPREQ_POST_FORM == data->set.httpreq) {
    data->req.bytecount = http->readbytecount + http->writebytecount;

    Curl_formclean(&http->sendit); 
    if(http->form.fp) {
      
      fclose(http->form.fp);
      http->form.fp = NULL;
    }
  }
  else if(HTTPREQ_PUT == data->set.httpreq)
    data->req.bytecount = http->readbytecount + http->writebytecount;

  if(status)
    return status;

  if(!premature && 
     !conn->bits.retry &&
     !data->set.connect_only &&
     ((http->readbytecount +
       data->req.headerbytecount -
       data->req.deductheadercount)) <= 0) {
    
    failf(data, "STR");
    return CURLE_GOT_NOTHING;
  }

  return CURLE_OK;
}