static void qcow_header_bswap(struct qcow_header *be, struct qcow_header *dst)
{
	dst->magic = be32toh(be->magic);
	dst->version = be32toh(be->version);
	dst->backing_file_offset = be64toh(be->backing_file_offset);
	dst->backing_file_size = be32toh(be->backing_file_size);
	dst->mtime = be32toh(be->mtime);
	dst->size = be64toh(be->size);
	dst->cluster_bits = be->cluster_bits;
	dst->l2_bits = be->l2_bits;
	dst->padding = be16toh(be->padding);
	dst->crypt_method = be32toh(be->crypt_method);
	dst->l1_table_offset = be64toh(be->l1_table_offset);
}