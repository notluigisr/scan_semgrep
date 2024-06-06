CURLcode Curl_build_unencoding_stack(struct Curl_easy *data,
                                     const char *enclist, int maybechunked)
{
  struct SingleRequest *k = &data->req;

  do {
    const char *name;
    size_t namelen;

    
    while(ISSPACE(*enclist) || *enclist == ',')
      enclist++;

    name = enclist;

    for(namelen = 0; *enclist && *enclist != ','; enclist++)
      if(!ISSPACE(*enclist))
        namelen = enclist - name + 1;

    
    if(maybechunked && namelen == 7 && strncasecompare(name, "STR", 7)) {
      k->chunk = TRUE;             
      Curl_httpchunk_init(data);   
    }
    else if(namelen) {
      const struct content_encoding *encoding = find_encoding(name, namelen);
      struct contenc_writer *writer;

      if(!k->writer_stack) {
        k->writer_stack = new_unencoding_writer(data, &client_encoding, NULL);

        if(!k->writer_stack)
          return CURLE_OUT_OF_MEMORY;
      }

      if(!encoding)
        encoding = &error_encoding;  

      
      writer = new_unencoding_writer(data, encoding, k->writer_stack);
      if(!writer)
        return CURLE_OUT_OF_MEMORY;
      k->writer_stack = writer;
    }
  } while(*enclist);

  return CURLE_OK;
}