static int test_alt_chains_cert_forgery(void)
{
    int ret = 0;
    int i;
    X509 *x = NULL;
    STACK_OF(X509) *untrusted = NULL;
    BIO *bio = NULL;
    X509_STORE_CTX *sctx = NULL;
    X509_STORE *store = NULL;
    X509_LOOKUP *lookup = NULL;

    store = X509_STORE_new();
    if (store == NULL)
        goto err;

    lookup = X509_STORE_add_lookup(store, X509_LOOKUP_file());
    if (lookup == NULL)
        goto err;
    if (!X509_LOOKUP_load_file(lookup, roots_f, X509_FILETYPE_PEM))
        goto err;

    untrusted = load_certs_from_file(untrusted_f);

    if ((bio = BIO_new_file(bad_f, "STR")) == NULL)
        goto err;

    if ((x = PEM_read_bio_X509(bio, NULL, 0, NULL)) == NULL)
        goto err;

    sctx = X509_STORE_CTX_new();
    if (sctx == NULL)
        goto err;

    if (!X509_STORE_CTX_init(sctx, store, x, untrusted))
        goto err;

    i = X509_verify_cert(sctx);

    if (i == 0 && X509_STORE_CTX_get_error(sctx) == X509_V_ERR_INVALID_CA) {
        
        ret = 1;
    }
 err:
    X509_STORE_CTX_free(sctx);
    X509_free(x);
    BIO_free(bio);
    sk_X509_pop_free(untrusted, X509_free);
    X509_STORE_free(store);
    return ret;
}