test_client_auth_request_fail (TestConnection *test,
                               gconstpointer   data)
{
  GIOStream *connection;
  GError *error = NULL;
  GTlsInteraction *interaction;

  test->database = g_tls_file_database_new (tls_test_file_path ("STR"), &error);
  g_assert_no_error (error);
  g_assert_nonnull (test->database);

  connection = start_async_server_and_connect_to_it (test, G_TLS_AUTHENTICATION_REQUIRED);
  test->client_connection = g_tls_client_connection_new (connection, test->identity, &error);
  g_assert_no_error (error);
  g_assert_nonnull (test->client_connection);
  g_object_unref (connection);

  g_tls_connection_set_database (G_TLS_CONNECTION (test->client_connection), test->database);

  
  interaction = mock_interaction_new_static_error (G_FILE_ERROR, G_FILE_ERROR_ACCES, "STR");
  g_tls_connection_set_interaction (G_TLS_CONNECTION (test->client_connection), interaction);
  g_object_unref (interaction);

  
  g_tls_client_connection_set_validation_flags (G_TLS_CLIENT_CONNECTION (test->client_connection),
                                                G_TLS_CERTIFICATE_VALIDATE_ALL);

  g_set_error_literal (&test->expected_client_close_error, G_TLS_ERROR, G_TLS_ERROR_CERTIFICATE_REQUIRED, "");

  read_test_data_async (test);
  g_main_loop_run (test->loop);
  wait_until_server_finished (test);

  
  g_assert_error (test->read_error, G_FILE_ERROR, G_FILE_ERROR_ACCES);
  g_assert_error (test->server_error, G_TLS_ERROR, G_TLS_ERROR_CERTIFICATE_REQUIRED);

  g_io_stream_close (test->server_connection, NULL, NULL);
  g_io_stream_close (test->client_connection, NULL, NULL);
}