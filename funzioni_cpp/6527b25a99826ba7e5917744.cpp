  Http::Http1::CodecStats& http1CodecStats() {
    return Http::Http1::CodecStats::atomicGet(http1_codec_stats_, stats_store_);
  }