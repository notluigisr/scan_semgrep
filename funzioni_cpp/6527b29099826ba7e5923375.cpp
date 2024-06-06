static SymbolsMetadata parseMetadata(RBuffer *buf, int off) {
	SymbolsMetadata sm = {0};
	ut8 b[0x100] = {0};
	(void)r_buf_read_at (buf, off, b, sizeof (b));
	sm.addr = off;
	sm.cputype = r_read_le32 (b);
	sm.arch = typeString (sm.cputype, &sm.bits);
	
	
	sm.subtype = r_read_le32 (b + 4);
	sm.cpu = subtypeString (sm.subtype);
	
	sm.n_segments = r_read_le32 (b + 8);
	
	sm.namelen = r_read_le32 (b + 0xc);
	
	
	
	int delta = 16;
	
	sm.size = (sm.n_segments * 32) + sm.namelen + delta;

	
	ut32 nm, nm2, nm3;
	r_buf_read_at (buf, off + sm.size, (ut8 *)&nm, sizeof (nm));
	r_buf_read_at (buf, off + sm.size + 4, (ut8 *)&nm2, sizeof (nm2));
	r_buf_read_at (buf, off + sm.size + 8, (ut8 *)&nm3, sizeof (nm3));
	
	if (r_read_le32 (&nm3) != 0xa1b22b1a) {
		sm.size -= 8;
		
	}
	return sm;
}