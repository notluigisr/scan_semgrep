static BROTLI_NOINLINE BrotliDecoderErrorCode SafeProcessCommands(
    BrotliDecoderState* s) {
  return ProcessCommandsInternal(1, s);
}