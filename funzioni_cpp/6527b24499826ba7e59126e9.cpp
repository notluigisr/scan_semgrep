DECLARESepPutFunc(putRGBAAseparate8bittile)
{
	(void) img; (void) x; (void) y; 
	for( ; h > 0; --h) {
		UNROLL8(w, NOP, *cp++ = PACK4(*r++, *g++, *b++, *a++));
		SKEW4(r, g, b, a, fromskew);
		cp += toskew;
	}
}