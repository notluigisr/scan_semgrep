zmq::curve_server_t::curve_server_t (session_base_t *session_,
                                     const std::string &peer_address_,
                                     const options_t &options_) :
    mechanism_t (options_),
    session (session_),
    peer_address (peer_address_),
    state (expect_hello),
    cn_nonce (1),
    sync()
{
    
    memcpy (secret_key, options_.curve_secret_key, crypto_box_SECRETKEYBYTES);
    scoped_lock_t lock (sync);
#if defined(HAVE_TWEETNACL)
    
    unsigned char tmpbytes[4];
    randombytes(tmpbytes, 4);
#else
    
    sodium_init();
#endif

    
    const int rc = crypto_box_keypair (cn_public, cn_secret);
    zmq_assert (rc == 0);
}