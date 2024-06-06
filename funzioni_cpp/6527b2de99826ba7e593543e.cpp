PHP_FUNCTION(radius_put_vendor_addr)
{
	long type, vendor;
	int addrlen;
	char	*addr;
	radius_descriptor *raddesc;
	zval *z_radh;
	struct in_addr intern_addr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &z_radh, &vendor,
		&type, &addr, &addrlen) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(raddesc, radius_descriptor *, &z_radh, -1, "STR", le_radius);

	if (inet_aton(addr, &intern_addr) == 0) {
		zend_error(E_ERROR, "STR");
		RETURN_FALSE;
	}

	if (rad_put_vendor_addr(raddesc->radh, vendor, type, intern_addr) == -1) {
		RETURN_FALSE;
	} else {
		RETURN_TRUE;
	}
}