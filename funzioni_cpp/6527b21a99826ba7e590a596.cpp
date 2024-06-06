PHP_MINFO_FUNCTION(exif)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "STR");
	php_info_print_table_row(2, "STR", PHP_EXIF_VERSION);
	php_info_print_table_row(2, "STR");
	php_info_print_table_row(2, "STR");

	if (zend_hash_str_exists(&module_registry, "STR")-1)) { 
		php_info_print_table_row(2, "STR");
	} else {
		php_info_print_table_row(2, "STR");
	}

	php_info_print_table_row(2, "STR");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}