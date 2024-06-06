static MagickBooleanType IsWEBPImageLossless(const unsigned char *stream,
  const size_t length)
{












  ssize_t
    offset;

  
  if (stream[VP8_CHUNK_INDEX] != EXTENDED_HEADER)
    return(stream[VP8_CHUNK_INDEX] == LOSSLESS_FLAG ? MagickTrue : MagickFalse);
  
  offset=RIFF_HEADER_SIZE+TAG_SIZE+CHUNK_SIZE_BYTES+VP8X_CHUNK_SIZE;
  while (offset <= (ssize_t) (length-TAG_SIZE))
  {
    uint32_t
      chunk_size,
      chunk_size_pad;

    chunk_size=ReadWebPLSBWord(stream+offset+TAG_SIZE);
    if (chunk_size > MAX_CHUNK_PAYLOAD)
      break;
    chunk_size_pad=(CHUNK_HEADER_SIZE+chunk_size+1) & ~1;
    if (memcmp(stream+offset,VP8_CHUNK_HEADER,VP8_CHUNK_HEADER_SIZE) == 0)
      return(*(stream+offset+VP8_CHUNK_HEADER_SIZE) == LOSSLESS_FLAG ?
        MagickTrue : MagickFalse);
    offset+=chunk_size_pad;
  }
  return(MagickFalse);
}