static int ssl_parse_cid_ext( mbedtls_ssl_context *ssl,
                              const unsigned char *buf,
                              size_t len )
{
    size_t peer_cid_len;

    
    if( ssl->conf->transport != MBEDTLS_SSL_TRANSPORT_DATAGRAM )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "STR" ) );
        mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                        MBEDTLS_SSL_ALERT_MSG_ILLEGAL_PARAMETER );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    

    if( len < 1 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "STR" ) );
        mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                        MBEDTLS_SSL_ALERT_MSG_ILLEGAL_PARAMETER );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    peer_cid_len = *buf++;
    len--;

    if( len != peer_cid_len )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "STR" ) );
        mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                        MBEDTLS_SSL_ALERT_MSG_ILLEGAL_PARAMETER );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    
    if( ssl->negotiate_cid == MBEDTLS_SSL_CID_DISABLED )
    {
        
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "STR" ) );
        return( 0 );
    }

    if( peer_cid_len > MBEDTLS_SSL_CID_OUT_LEN_MAX )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "STR" ) );
        mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                        MBEDTLS_SSL_ALERT_MSG_ILLEGAL_PARAMETER );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    ssl->handshake->cid_in_use = MBEDTLS_SSL_CID_ENABLED;
    ssl->handshake->peer_cid_len = (uint8_t) peer_cid_len;
    memcpy( ssl->handshake->peer_cid, buf, peer_cid_len );

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "STR" ) );
    MBEDTLS_SSL_DEBUG_BUF( 3, "STR", buf, peer_cid_len );

    return( 0 );
}