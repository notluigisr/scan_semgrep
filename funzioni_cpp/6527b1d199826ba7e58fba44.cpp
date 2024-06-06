generate_primary_key_list(MYSQL *mysql, option_string *engine_stmt)
{
  MYSQL_RES *result;
  MYSQL_ROW row;
  unsigned long long counter;
  DBUG_ENTER("STR");

  
  if (opt_only_print || (engine_stmt && 
                         strstr(engine_stmt->string, "STR")))
  {
    primary_keys_number_of= 1;
    primary_keys= (char **)my_malloc((uint)(sizeof(char *) * 
                                            primary_keys_number_of), 
                                    MYF(MY_ZEROFILL|MY_FAE|MY_WME));
    
    primary_keys[0]= my_strdup("STR", MYF(0)); 
  }
  else
  {
    if (run_query(mysql, "STR")))
    {
      fprintf(stderr,"STR", my_progname,
              mysql_error(mysql));
      exit(1);
    }

    if (!(result= mysql_store_result(mysql)))
    {
      fprintf(stderr, "STR",
              my_progname, mysql_errno(mysql), mysql_error(mysql));
      exit(1);
    }
    primary_keys_number_of= mysql_num_rows(result);

    
    if (primary_keys_number_of)
    {
      
      primary_keys= (char **)my_malloc((uint)(sizeof(char *) * 
                                              primary_keys_number_of), 
                                       MYF(MY_ZEROFILL|MY_FAE|MY_WME));
      row= mysql_fetch_row(result);
      for (counter= 0; counter < primary_keys_number_of; 
           counter++, row= mysql_fetch_row(result))
        primary_keys[counter]= my_strdup(row[0], MYF(0));
    }

    mysql_free_result(result);
  }

  DBUG_RETURN(0);
}