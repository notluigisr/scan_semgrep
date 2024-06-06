int wc_SetSubject(Cert* cert, const char* subjectFile)
{
    int         ret;
    int         derSz;
    byte*       der;

    if (cert == NULL) {
        return BAD_FUNC_ARG;
    }

    der = (byte*)XMALLOC(EIGHTK_BUF, cert->heap, DYNAMIC_TYPE_CERT);
    if (der == NULL) {
        WOLFSSL_MSG("STR");
        return MEMORY_E;
    }

    derSz = wc_PemCertToDer(subjectFile, der, EIGHTK_BUF);
    ret = SetNameFromCert(&cert->subject, der, derSz);
    XFREE(der, cert->heap, DYNAMIC_TYPE_CERT);

    return ret;
}