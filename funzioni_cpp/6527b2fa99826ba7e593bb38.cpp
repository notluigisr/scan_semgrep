static long bio_zlib_callback_ctrl(BIO *b, int cmd, bio_info_cb *fp)
	{
	if(!b->next_bio)
		return 0;
	return
		BIO_callback_ctrl(b->next_bio, cmd, fp);
	}