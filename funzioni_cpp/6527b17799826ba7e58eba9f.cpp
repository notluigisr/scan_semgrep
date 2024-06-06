static zend_bool add_post_var(zval *arr, post_var_data_t *var, zend_bool eof TSRMLS_DC)
{
	char *ksep, *vsep;
	size_t klen, vlen;
	
	unsigned int new_vlen;

	if (var->ptr >= var->end) {
		return 0;
	}

	vsep = memchr(var->ptr, '&', var->end - var->ptr);
	if (!vsep) {
		if (!eof) {
			return 0;
		} else {
			vsep = var->end;
		}
	}

	ksep = memchr(var->ptr, '=', vsep - var->ptr);
	if (ksep) {
		*ksep = '\0';
		
		klen = ksep - var->ptr;
		vlen = vsep - ++ksep;
	} else {
		ksep = "";
		
		klen = vsep - var->ptr;
		vlen = 0;
	}


	php_url_decode(var->ptr, klen);
	if (vlen) {
		vlen = php_url_decode(ksep, vlen);
	}

	if (sapi_module.input_filter(PARSE_POST, var->ptr, &ksep, vlen, &new_vlen TSRMLS_CC)) {
		php_register_variable_safe(var->ptr, ksep, new_vlen, arr TSRMLS_CC);
	}

	var->ptr = vsep + (vsep != var->end);
	return 1;
}