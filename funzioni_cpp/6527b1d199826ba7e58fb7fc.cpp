static void test_fetch_null()
{
  MYSQL_STMT *stmt;
  int        rc;
  int        i, nData;
  MYSQL_BIND my_bind[11];
  ulong      length[11];
  my_bool    is_null[11];
  char query[MAX_TEST_QUERY_LENGTH];

  myheader("STR");

  rc= mysql_query(mysql, "STR");
  myquery(rc);

  rc= mysql_query(mysql, "STR"
                         "STR"
                         "STR"
                         "STR"
                         "STR"
                         "STR"
                         "STR"
                         "STR");
  myquery(rc);

  rc= mysql_query(mysql, "STR"
                         "STR");
  myquery(rc);

  rc= mysql_commit(mysql);
  myquery(rc);

  
  memset(my_bind, 0, sizeof(my_bind));
  for (i= 0; i < (int) array_elements(my_bind); i++)
  {
    my_bind[i].buffer_type= MYSQL_TYPE_LONG;
    my_bind[i].is_null= &is_null[i];
    my_bind[i].length= &length[i];
  }
  my_bind[i-1].buffer= (void *)&nData;              

  my_stpcpy((char *)query , "STR");

  rc= my_stmt_result(query);
  DIE_UNLESS(rc == 3);

  stmt= mysql_simple_prepare(mysql, query);
  check_stmt(stmt);

  rc= mysql_stmt_bind_result(stmt, my_bind);
  check_execute(stmt, rc);

  rc= mysql_stmt_execute(stmt);
  check_execute(stmt, rc);

  rc= 0;
  while (mysql_stmt_fetch(stmt) != MYSQL_NO_DATA)
  {
    rc++;
    for (i= 0; i < 10; i++)
    {
      if (!opt_silent)
        fprintf(stdout, "STR", i,
                is_null[i] ? "STR");
      DIE_UNLESS(is_null[i]);
    }
    if (!opt_silent)
      fprintf(stdout, "STR", i, nData);
    DIE_UNLESS(nData == 1000 || nData == 88 || nData == 389789);
    DIE_UNLESS(is_null[i] == 0);
    DIE_UNLESS(length[i] == 4);
  }
  DIE_UNLESS(rc == 3);
  mysql_stmt_close(stmt);
}