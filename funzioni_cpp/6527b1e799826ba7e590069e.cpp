void LOGGER::init_base()
{
  DBUG_ASSERT(inited == 0);
  inited= 1;

  
  if (!file_log_handler)
    file_log_handler= new Log_to_file_event_handler;

  
  init_error_log(LOG_FILE);

  file_log_handler->init_pthread_objects();
  mysql_rwlock_init(key_rwlock_LOCK_logger, &LOCK_logger);
}