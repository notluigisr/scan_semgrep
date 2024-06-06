GF_Err tenc_dump(GF_Box *a, FILE * trace)
{
	GF_TrackEncryptionBox *ptr = (GF_TrackEncryptionBox*) a;
	if (!a) return GF_BAD_PARAM;

	gf_isom_box_dump_start(a, "STR", trace);

	fprintf(trace, "STR", ptr->isProtected);
	if (ptr->Per_Sample_IV_Size)
		fprintf(trace, "STR", ptr->Per_Sample_IV_Size);
	else {
		fprintf(trace, "STR", ptr->constant_IV_size);
		dump_data_hex(trace, (char *) ptr->constant_IV, ptr->constant_IV_size);
		fprintf(trace, "STR");
	}
	dump_data_hex(trace, (char *) ptr->KID, 16);
	if (ptr->version) 
		fprintf(trace, "STR", ptr->crypt_byte_block, ptr->skip_byte_block);
	fprintf(trace, "STR");
	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}