glue(glue(cirrus_bitblt_rop_fwd_transp_, ROP_NAME),_16)(CirrusVGAState *s,
							uint8_t *dst,const uint8_t *src,
							int dstpitch,int srcpitch,
							int bltwidth,int bltheight)
{
    int x,y;
    uint8_t p1, p2;
    dstpitch -= bltwidth;
    srcpitch -= bltwidth;

    if (bltheight > 1 && (dstpitch < 0 || srcpitch < 0)) {
        return;
    }

    for (y = 0; y < bltheight; y++) {
        for (x = 0; x < bltwidth; x+=2) {
	    p1 = *dst;
	    p2 = *(dst+1);
            ROP_OP(&p1, *src);
            ROP_OP(&p2, *(src + 1));
	    if ((p1 != s->vga.gr[0x34]) || (p2 != s->vga.gr[0x35])) {
		*dst = p1;
		*(dst+1) = p2;
	    }
            dst+=2;
            src+=2;
        }
        dst += dstpitch;
        src += srcpitch;
    }
}