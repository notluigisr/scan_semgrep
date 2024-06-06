CURLcode Curl_close(struct SessionHandle *data)
{
  struct Curl_multi *m;

  if(!data)
    return CURLE_OK;

  Curl_expire(data, 0); 

  m = data->multi;

  if(m)
    
    curl_multi_remove_handle(data->multi, data);

  if(data->multi_easy)
    
    curl_multi_cleanup(data->multi_easy);

  
  if(data->state.timeoutlist) {
    Curl_llist_destroy(data->state.timeoutlist, NULL);
    data->state.timeoutlist = NULL;
  }

  data->magic = 0; 

  if(data->state.rangestringalloc)
    free(data->state.range);

  
  Curl_safefree(data->state.pathbuffer);
  data->state.path = NULL;

  
  Curl_free_request_state(data);

  
  Curl_ssl_close_all(data);
  Curl_safefree(data->state.first_host);
  Curl_safefree(data->state.scratch);
  Curl_ssl_free_certinfo(data);

  
  if(data->req.newurl) {
    free(data->req.newurl);
    data->req.newurl = NULL;
  }

  if(data->change.referer_alloc) {
    Curl_safefree(data->change.referer);
    data->change.referer_alloc = FALSE;
  }
  data->change.referer = NULL;

  if(data->change.url_alloc) {
    Curl_safefree(data->change.url);
    data->change.url_alloc = FALSE;
  }
  data->change.url = NULL;

  Curl_safefree(data->state.headerbuff);

  Curl_flush_cookies(data, 1);

  Curl_digest_cleanup(data);

  Curl_safefree(data->info.contenttype);
  Curl_safefree(data->info.wouldredirect);

  
  Curl_resolver_cleanup(data->state.resolver);

  Curl_convert_close(data);

  
  if(data->share) {
    Curl_share_lock(data, CURL_LOCK_DATA_SHARE, CURL_LOCK_ACCESS_SINGLE);
    data->share->dirty--;
    Curl_share_unlock(data, CURL_LOCK_DATA_SHARE);
  }

  Curl_freeset(data);
  free(data);
  return CURLE_OK;
}