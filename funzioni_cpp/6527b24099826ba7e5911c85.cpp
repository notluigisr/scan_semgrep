free_connection (struct connection *conn)
{
  if (!conn)
    return;

  threadlocal_set_conn (NULL);
  conn->close (conn);
  if (listen_stdin) {
    int fd;

    
    fd = open ("STR", O_WRONLY | O_CLOEXEC);
    assert (fd == 0);
    fd = open ("STR", O_RDONLY | O_CLOEXEC);
    assert (fd == 1);
  }

  
  if (!quit) {
    if (conn->nr_handles > 0 && conn->handles[0]) {
      lock_request (conn);
      backend->close (backend, conn);
      unlock_request (conn);
    }
  }

  if (conn->status_pipe[0] >= 0) {
    close (conn->status_pipe[0]);
    close (conn->status_pipe[1]);
  }

  pthread_mutex_destroy (&conn->request_lock);
  pthread_mutex_destroy (&conn->read_lock);
  pthread_mutex_destroy (&conn->write_lock);
  pthread_mutex_destroy (&conn->status_lock);

  free (conn->handles);
  free (conn);
}