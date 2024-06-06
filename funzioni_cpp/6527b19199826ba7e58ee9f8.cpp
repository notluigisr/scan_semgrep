int wc_SignatureGenerate(
    enum wc_HashType hash_type, enum wc_SignatureType sig_type,
    const byte* data, word32 data_len,
    byte* sig, word32 *sig_len,
    const void* key, word32 key_len, WC_RNG* rng)
{
    int ret;
    word32 hash_len, hash_enc_len;
#ifdef WOLFSSL_SMALL_STACK
    byte *hash_data;
#else
    byte hash_data[MAX_DER_DIGEST_SZ];
#endif

    
    if (data == NULL || data_len <= 0 ||
        sig == NULL || sig_len == NULL || *sig_len <= 0 ||
        key == NULL || key_len <= 0) {
        return BAD_FUNC_ARG;
    }

    
    if ((int)*sig_len < wc_SignatureGetSize(sig_type, key, key_len)) {
        WOLFSSL_MSG("STR");
        return BAD_FUNC_ARG;
    }

    
    ret = wc_HashGetDigestSize(hash_type);
    if (ret < 0) {
        WOLFSSL_MSG("STR");
        return ret;
    }
    hash_enc_len = hash_len = ret;

#if !defined(NO_RSA) && !defined(WOLFSSL_RSA_PUBLIC_ONLY)
    if (sig_type == WC_SIGNATURE_TYPE_RSA_W_ENC) {
        
        hash_enc_len += MAX_DER_DIGEST_ASN_SZ;
    }
#endif

#ifdef WOLFSSL_SMALL_STACK
    
    hash_data = (byte*)XMALLOC(hash_enc_len, NULL, DYNAMIC_TYPE_TMP_BUFFER);
    if (hash_data == NULL) {
        return MEMORY_E;
    }
#endif

    
    ret = wc_Hash(hash_type, data, data_len, hash_data, hash_len);
    if (ret == 0) {
        
        if (sig_type == WC_SIGNATURE_TYPE_RSA_W_ENC) {
        #if defined(NO_RSA) || defined(NO_ASN) || \
                                                defined(WOLFSSL_RSA_PUBLIC_ONLY)
            ret = SIG_TYPE_E;
        #else
            ret = wc_SignatureDerEncode(hash_type, hash_data, hash_len,
                &hash_enc_len);
        #endif
        }

        if (ret == 0) {
            
            ret = wc_SignatureGenerateHash(hash_type, sig_type,
                hash_data, hash_enc_len, sig, sig_len, key, key_len, rng);
        }
    }

#ifdef WOLFSSL_SMALL_STACK
    XFREE(hash_data, NULL, DYNAMIC_TYPE_TMP_BUFFER);
#endif

    return ret;
}