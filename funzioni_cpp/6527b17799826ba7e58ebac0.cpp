static int ssl_parse_supported_elliptic_curves( ssl_context *ssl,
                                                const unsigned char *buf,
                                                size_t len )
{
    size_t list_size, our_size;
    const unsigned char *p;
    const ecp_curve_info *curve_info, **curves;

    list_size = ( ( buf[0] << 8 ) | ( buf[1] ) );
    if( list_size + 2 != len ||
        list_size % 2 != 0 )
    {
        SSL_DEBUG_MSG( 1, ( "STR" ) );
        return( POLARSSL_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    
    our_size = list_size / 2 + 1;
    if( our_size > POLARSSL_ECP_DP_MAX )
        our_size = POLARSSL_ECP_DP_MAX;

    if( ( curves = polarssl_malloc( our_size * sizeof( *curves ) ) ) == NULL )
        return( POLARSSL_ERR_SSL_MALLOC_FAILED );

    
    memset( (void *) curves, 0, our_size * sizeof( *curves ) );
    ssl->handshake->curves = curves;

    p = buf + 2;
    while( list_size > 0 && our_size > 1 )
    {
        curve_info = ecp_curve_info_from_tls_id( ( p[0] << 8 ) | p[1] );

        if( curve_info != NULL )
        {
            *curves++ = curve_info;
            our_size--;
        }

        list_size -= 2;
        p += 2;
    }

    return( 0 );
}