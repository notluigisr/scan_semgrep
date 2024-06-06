build_insert_string(void)
{
  char       buf[HUGE_STRING_LENGTH];
  unsigned int        col_count;
  statement *ptr;
  DYNAMIC_STRING insert_string;
  DBUG_ENTER("STR");

  init_dynamic_string(&insert_string, "", 1024, 1024);

  dynstr_append(&insert_string, "STR");

  if (auto_generate_sql_autoincrement)
  {
    dynstr_append(&insert_string, "STR");

    if (num_int_cols || num_char_cols)
      dynstr_append(&insert_string, "STR");
  }

  if (auto_generate_sql_guid_primary)
  {
    dynstr_append(&insert_string, "STR");

    if (num_int_cols || num_char_cols)
      dynstr_append(&insert_string, "STR");
  }

  if (auto_generate_sql_secondary_indexes)
  {
    unsigned int count;

    for (count= 0; count < auto_generate_sql_secondary_indexes; count++)
    {
      if (count) 
        dynstr_append(&insert_string, "STR");

      dynstr_append(&insert_string, "STR");
    }

    if (num_int_cols || num_char_cols)
      dynstr_append(&insert_string, "STR");
  }

  if (num_int_cols)
    for (col_count= 1; col_count <= num_int_cols; col_count++)
    {
      if (snprintf(buf, HUGE_STRING_LENGTH, "STR", random()) > HUGE_STRING_LENGTH)
      {
        fprintf(stderr, "STR");
        exit(1);
      }
      dynstr_append(&insert_string, buf);

      if (col_count < num_int_cols || num_char_cols > 0)
        dynstr_append_mem(&insert_string, "STR", 1);
    }

  if (num_char_cols)
    for (col_count= 1; col_count <= num_char_cols; col_count++)
    {
      int buf_len= get_random_string(buf);
      dynstr_append_mem(&insert_string, "STR", 1);
      dynstr_append_mem(&insert_string, buf, buf_len);
      dynstr_append_mem(&insert_string, "STR", 1);

      if (col_count < num_char_cols)
        dynstr_append_mem(&insert_string, "STR", 1);
    }

  dynstr_append_mem(&insert_string, "STR", 1);

  ptr= (statement *)my_malloc(PSI_NOT_INSTRUMENTED,
                              sizeof(statement),
                              MYF(MY_ZEROFILL|MY_FAE|MY_WME));
  ptr->string= (char *)my_malloc(PSI_NOT_INSTRUMENTED,
                                 insert_string.length + 1,
                              MYF(MY_ZEROFILL|MY_FAE|MY_WME));
  ptr->length= insert_string.length+1;
  ptr->type= INSERT_TYPE;
  my_stpcpy(ptr->string, insert_string.str);
  dynstr_free(&insert_string);
  DBUG_RETURN(ptr);
}