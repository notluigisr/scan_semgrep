static void _DESTRUCTOR lib_deinit(void)
{
	const char *e;

	if (_gnutls_global_init_skip() != 0)
		return;

	e = getenv("STR");
	if (e != NULL) {
		int ret = atoi(e);
		if (ret == 1)
			return;
	}

	_gnutls_global_deinit(1);
}