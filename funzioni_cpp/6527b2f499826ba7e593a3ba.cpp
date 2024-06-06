String *Item_param::PValue::val_str(String *str,
                                    const Type_std_attributes *attr)
{
  switch (type_handler()->cmp_type()) {
  case STRING_RESULT:
    return &m_string_ptr;
  case REAL_RESULT:
    str->set_real(real, NOT_FIXED_DEC, &my_charset_bin);
    return str;
  case INT_RESULT:
    str->set_int(integer, attr->unsigned_flag, &my_charset_bin);
    return str;
  case DECIMAL_RESULT:
    if (my_decimal2string(E_DEC_FATAL_ERROR, &m_decimal, 0, 0, 0, str) <= 1)
      return str;
    return NULL;
  case TIME_RESULT:
  {
    if (str->reserve(MAX_DATE_STRING_REP_LENGTH))
      return NULL;
    str->length((uint) my_TIME_to_str(&time, (char*) str->ptr(),
                attr->decimals));
    str->set_charset(&my_charset_bin);
    return str;
  }
  case ROW_RESULT:
    DBUG_ASSERT(0);
    break;
  }
  return NULL;
}