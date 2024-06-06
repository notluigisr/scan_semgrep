static int lmf_header_load(lmf_header *lmfh, RBuffer *buf, Sdb *db) {
	if (r_buf_size (buf) < sizeof (lmf_header)) {
		return false;
	}
	if (r_buf_fread_at (buf, QNX_HEADER_ADDR, (ut8 *) lmfh, "STR", 1) < QNX_HDR_SIZE) {
		return false;
	}
	r_strf_buffer (32);
	sdb_set (db, "STR", lmfh->version), 0);
	sdb_set (db, "STR", lmfh->cflags), 0);
	sdb_set (db, "STR", lmfh->cpu), 0);
	sdb_set (db, "STR", lmfh->fpu), 0);
	sdb_set (db, "STR", lmfh->code_index), 0);
	sdb_set (db, "STR", lmfh->stack_index), 0);
	sdb_set (db, "STR", lmfh->heap_index), 0);
	sdb_set (db, "STR", lmfh->argv_index), 0);
	sdb_set (db, "STR", lmfh->code_offset), 0);
	sdb_set (db, "STR", lmfh->stack_nbytes), 0);
	sdb_set (db, "STR", lmfh->heap_nbytes), 0);
	sdb_set (db, "STR", lmfh->image_base), 0);
	return true;
}