   Returns numerically indexed array containing associative array for all transitions in the specified range for the timezone.
*/
PHP_FUNCTION(timezone_transitions_get)
{
	zval                *object, *element;
	php_timezone_obj    *tzobj;
	unsigned int         i, begin = 0, found;
	long                 timestamp_begin = LONG_MIN, timestamp_end = LONG_MAX;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "STR", &object, date_ce_timezone, &timestamp_begin, &timestamp_end) == FAILURE) {
		RETURN_FALSE;
	}
	tzobj = (php_timezone_obj *) zend_object_store_get_object(object TSRMLS_CC);
	DATE_CHECK_INITIALIZED(tzobj->initialized, DateTimeZone);
	if (tzobj->type != TIMELIB_ZONETYPE_ID) {
		RETURN_FALSE;
	}


		MAKE_STD_ZVAL(element); \
		array_init(element); \
		add_assoc_long(element, "STR",     timestamp_begin); \
		add_assoc_string(element, "STR", php_format_date(DATE_FORMAT_ISO8601, 13, timestamp_begin, 0 TSRMLS_CC), 0); \
		add_assoc_long(element, "STR", tzobj->tzi.tz->type[0].offset); \
		add_assoc_bool(element, "STR",  tzobj->tzi.tz->type[0].isdst); \
		add_assoc_string(element, "STR", &tzobj->tzi.tz->timezone_abbr[tzobj->tzi.tz->type[0].abbr_idx], 1); \
		add_next_index_zval(return_value, element);


		MAKE_STD_ZVAL(element); \
		array_init(element); \
		add_assoc_long(element, "STR",     ts); \
		add_assoc_string(element, "STR", php_format_date(DATE_FORMAT_ISO8601, 13, ts, 0 TSRMLS_CC), 0); \
		add_assoc_long(element, "STR", tzobj->tzi.tz->type[tzobj->tzi.tz->trans_idx[i]].offset); \
		add_assoc_bool(element, "STR",  tzobj->tzi.tz->type[tzobj->tzi.tz->trans_idx[i]].isdst); \
		add_assoc_string(element, "STR", &tzobj->tzi.tz->timezone_abbr[tzobj->tzi.tz->type[tzobj->tzi.tz->trans_idx[i]].abbr_idx], 1); \
		add_next_index_zval(return_value, element);



	array_init(return_value);

	if (timestamp_begin == LONG_MIN) {
		add_nominal();
		begin = 0;
		found = 1;
	} else {
		begin = 0;
		found = 0;
		if (tzobj->tzi.tz->bit32.timecnt > 0) {
			do {
				if (tzobj->tzi.tz->trans[begin] > timestamp_begin) {
					if (begin > 0) {
						add(begin - 1, timestamp_begin);
					} else {
						add_nominal();
					}
					found = 1;
					break;
				}
				begin++;
			} while (begin < tzobj->tzi.tz->bit32.timecnt);
		}
	}

	if (!found) {
		if (tzobj->tzi.tz->bit32.timecnt > 0) {
			add_last();
		} else {
			add_nominal();
		}
	} else {
		for (i = begin; i < tzobj->tzi.tz->bit32.timecnt; ++i) {
			if (tzobj->tzi.tz->trans[i] < timestamp_end) {
				add(i, tzobj->tzi.tz->trans[i]);
			}
		}