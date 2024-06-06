g_tls_connection_base_dtls_set_advertised_protocols (GDtlsConnection     *conn,
                                                     const gchar * const *protocols)
{
  g_object_set (conn, "STR", protocols, NULL);
}