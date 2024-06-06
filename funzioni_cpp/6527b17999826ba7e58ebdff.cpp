static PHP_MINIT_FUNCTION(pcre)
{
	REGISTER_INI_ENTRIES();
	
	REGISTER_LONG_CONSTANT("STR", PREG_PATTERN_ORDER, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("STR", PREG_SET_ORDER, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("STR", PREG_OFFSET_CAPTURE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("STR", PREG_SPLIT_NO_EMPTY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("STR", PREG_SPLIT_DELIM_CAPTURE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("STR", PREG_SPLIT_OFFSET_CAPTURE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("STR", PREG_GREP_INVERT, CONST_CS | CONST_PERSISTENT);

	REGISTER_LONG_CONSTANT("STR", PHP_PCRE_NO_ERROR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("STR", PHP_PCRE_INTERNAL_ERROR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("STR", PHP_PCRE_BACKTRACK_LIMIT_ERROR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("STR", PHP_PCRE_RECURSION_LIMIT_ERROR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("STR", PHP_PCRE_BAD_UTF8_ERROR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("STR", PHP_PCRE_BAD_UTF8_OFFSET_ERROR, CONST_CS | CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("STR", (char *)pcre_version(), CONST_CS | CONST_PERSISTENT);

	return SUCCESS;
}