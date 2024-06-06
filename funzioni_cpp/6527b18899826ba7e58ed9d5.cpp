static BROTLI_INLINE uint32_t BlockLengthPrefixCode(uint32_t len) {
  uint32_t code = (len >= 177) ? (len >= 753 ? 20 : 14) : (len >= 41 ? 7 : 0);
  while (code < (BROTLI_NUM_BLOCK_LEN_SYMBOLS - 1) &&
      len >= kBlockLengthPrefixCode[code + 1].offset) ++code;
  return code;
}