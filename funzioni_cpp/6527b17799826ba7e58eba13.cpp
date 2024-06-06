PHP_FUNCTION(ftok)
{
	char *pathname, *proj;
	int pathname_len, proj_len;
	key_t k;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &pathname, &pathname_len, &proj, &proj_len) == FAILURE) {
		return;
	}

	if (pathname_len == 0){
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
		RETURN_LONG(-1);
	}

	if (proj_len != 1){
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
		RETURN_LONG(-1);
    }

	if ((PG(safe_mode) && (!php_checkuid(pathname, NULL, CHECKUID_CHECK_FILE_AND_DIR))) || php_check_open_basedir(pathname TSRMLS_CC)) {
		RETURN_LONG(-1);
	}

	k = ftok(pathname, proj[0]);
	if (k == -1) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", strerror(errno));
	}

	RETURN_LONG(k);
}