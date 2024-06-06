char *Item_func_password::
  create_password_hash_buffer(THD *thd, const char *password,  size_t pass_len)
{
  String *password_str= new (thd->mem_root)String(password, thd->variables.
                                                    character_set_client);
  check_password_policy(password_str);

  char *buff= NULL;
  if (thd->variables.old_passwords == 0)
  {
    
    buff= (char *) thd->alloc(SCRAMBLED_PASSWORD_CHAR_LENGTH + 1);
    my_make_scrambled_password_sha1(buff, password, pass_len);
  }
#if defined(HAVE_OPENSSL)
  else
  {
    
    buff= (char *) thd->alloc(CRYPT_MAX_PASSWORD_SIZE + 1);
    my_make_scrambled_password(buff, password, pass_len);
  }
#endif
  return buff;
}