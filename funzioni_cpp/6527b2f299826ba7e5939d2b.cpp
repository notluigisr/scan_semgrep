void SSL_set_client_CA_list(SSL *s, STACK_OF(X509_NAME) *name_list)
{
    set0_CA_list(&s->client_ca_names, name_list);
}