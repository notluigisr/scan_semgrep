PHP_FUNCTION(locale_compose)
{
	smart_str      	loc_name_s = {0};
	smart_str *loc_name = &loc_name_s;
	zval*			arr	= NULL;
	HashTable*		hash_arr = NULL;
	int 			result = 0;

	intl_error_reset( NULL TSRMLS_CC );

	if(zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "STR",
		&arr) == FAILURE)
	{
		intl_error_set( NULL, U_ILLEGAL_ARGUMENT_ERROR,
			 "STR", 0 TSRMLS_CC );
		RETURN_FALSE;
	}

	hash_arr = HASH_OF( arr );

	if( !hash_arr || zend_hash_num_elements( hash_arr ) == 0 )
		RETURN_FALSE;

	
	result = append_key_value(loc_name, hash_arr,  LOC_GRANDFATHERED_LANG_TAG);	
	if( result == SUCCESS){
		RETURN_SMART_STR(loc_name);
	}
	if( !handleAppendResult( result, loc_name TSRMLS_CC)){
		RETURN_FALSE;
	}

	
	result = append_key_value(loc_name, hash_arr , LOC_LANG_TAG);	
	if( result == LOC_NOT_FOUND ){
		intl_error_set( NULL, U_ILLEGAL_ARGUMENT_ERROR,
		"STR", 0 TSRMLS_CC );
		smart_str_free(loc_name);
		RETURN_FALSE;
	}
	if( !handleAppendResult( result, loc_name TSRMLS_CC)){
		RETURN_FALSE;
	}

	
	result = append_multiple_key_values(loc_name, hash_arr , LOC_EXTLANG_TAG TSRMLS_CC);
	if( !handleAppendResult( result, loc_name TSRMLS_CC)){
		RETURN_FALSE;
	}

	
	result = append_key_value(loc_name, hash_arr , LOC_SCRIPT_TAG); 
	if( !handleAppendResult( result, loc_name TSRMLS_CC)){
		RETURN_FALSE;
	}
	
	
	result = append_key_value( loc_name, hash_arr , LOC_REGION_TAG);
	if( !handleAppendResult( result, loc_name TSRMLS_CC)){
		RETURN_FALSE;
	}

	
	result = append_multiple_key_values( loc_name, hash_arr , LOC_VARIANT_TAG TSRMLS_CC); 
	if( !handleAppendResult( result, loc_name TSRMLS_CC)){
		RETURN_FALSE;
	}

	
	result = append_multiple_key_values( loc_name, hash_arr , LOC_PRIVATE_TAG TSRMLS_CC);
	if( !handleAppendResult( result, loc_name TSRMLS_CC)){
		RETURN_FALSE;
	}

	RETURN_SMART_STR(loc_name);
}