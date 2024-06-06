static void test_long_data()
{
  MYSQL_STMT *stmt;
  int        rc, int_data;
  char       *data= NullS;
  MYSQL_RES  *result;
  MYSQL_BIND my_bind[3];
  char query[MAX_TEST_QUERY_LENGTH];

  myheader("STR");

  rc= mysql_autocommit(mysql, TRUE);
  myquery(rc);

  rc= mysql_query(mysql, "STR");
  myquery(rc);

  rc= mysql_query(mysql, "STR"
                         "STR");
  myquery(rc);

  my_stpcpy(query, "STR");
  stmt= mysql_simple_prepare(mysql, query);
  check_stmt_r(stmt);

  my_stpcpy(query, "STR");
  stmt= mysql_simple_prepare(mysql, query);
  check_stmt(stmt);

  verify_param_count(stmt, 3);

  
  memset(my_bind, 0, sizeof(my_bind));

  my_bind[0].buffer= (void *)&int_data;
  my_bind[0].buffer_type= MYSQL_TYPE_LONG;

  my_bind[1].buffer_type= MYSQL_TYPE_STRING;

  my_bind[2]= my_bind[1];
  rc= mysql_stmt_bind_param(stmt, my_bind);
  check_execute(stmt, rc);

  int_data= 999;
  data= (char *)"STR";

  
  rc= mysql_stmt_send_long_data(stmt, 1, data, strlen(data));
  data= (char *)"STR";
  rc= mysql_stmt_send_long_data(stmt, 1, data, strlen(data));
  check_execute(stmt, rc);
  rc= mysql_stmt_send_long_data(stmt, 2, "STR", 4);
  check_execute(stmt, rc);

  
  rc= mysql_stmt_execute(stmt);
  if (!opt_silent)
    fprintf(stdout, "STR", rc);
  check_execute(stmt, rc);

  rc= mysql_commit(mysql);
  myquery(rc);

  
  rc= mysql_query(mysql, "STR");
  myquery(rc);

  
  result= mysql_store_result(mysql);
  mytest(result);

  rc= my_process_result_set(result);
  DIE_UNLESS(rc == 1);
  mysql_free_result(result);

  verify_col_data("STR");
  verify_col_data("STR");
  verify_col_data("STR");
  mysql_stmt_close(stmt);
}