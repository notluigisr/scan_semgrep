static void ZRLE_ENCODE (int x, int y, int w, int h,
		  zrleOutStream* os, void* buf
                  EXTRA_ARGS
                  )
{
  int ty;
  for (ty = y; ty < y+h; ty += rfbZRLETileHeight) {
    int tx, th = rfbZRLETileHeight;
    if (th > y+h-ty) th = y+h-ty;
    for (tx = x; tx < x+w; tx += rfbZRLETileWidth) {
      int tw = rfbZRLETileWidth;
      if (tw > x+w-tx) tw = x+w-tx;

      GET_IMAGE_INTO_BUF(tx,ty,tw,th,buf);

      ZRLE_ENCODE_TILE((PIXEL_T*)buf, tw, th, os,
		      cl->zywrleLevel, cl->zywrleBuf);
    }
  }
  zrleOutStreamFlush(os);
}