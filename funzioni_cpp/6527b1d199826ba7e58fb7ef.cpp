static void test_bug11037()
{
  MYSQL_STMT *stmt;
  int rc;
  const char *stmt_text;

  myheader("STR");

  mysql_query(mysql, "STR");

  rc= mysql_query(mysql, "STR");
  myquery(rc);

  rc= mysql_query(mysql, "STR");
  myquery(rc);

  stmt_text= "STR";
  stmt= mysql_stmt_init(mysql);
  rc= mysql_stmt_prepare(stmt, stmt_text, strlen(stmt_text));

  
  rc = mysql_stmt_fetch(stmt);
  DIE_UNLESS(rc==1);
  if (!opt_silent)
    fprintf(stdout, "STR",
            mysql_stmt_errno(stmt), mysql_stmt_error(stmt));

  rc= mysql_stmt_execute(stmt);
  check_execute(stmt, rc);

  rc= mysql_stmt_fetch(stmt);
  DIE_UNLESS(rc==0);

  rc= mysql_stmt_fetch(stmt);
  DIE_UNLESS(rc==MYSQL_NO_DATA);

  rc= mysql_stmt_fetch(stmt);
  DIE_UNLESS(rc==MYSQL_NO_DATA);

  mysql_stmt_close(stmt);
  rc= mysql_query(mysql, "STR");
  myquery(rc);
}