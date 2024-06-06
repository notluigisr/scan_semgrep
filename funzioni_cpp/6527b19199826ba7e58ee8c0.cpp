TPMI_ALG_ASYM_SCHEME_Unmarshal(TPMI_ALG_ASYM_SCHEME *target, BYTE **buffer, INT32 *size, BOOL allowNull)
{
    TPM_RC rc = TPM_RC_SUCCESS;

    if (rc == TPM_RC_SUCCESS) {
	rc = TPM_ALG_ID_Unmarshal(target, buffer, size);  
    }
    if (rc == TPM_RC_SUCCESS) {
	switch (*target) {
#if ALG_ECDH
	  case TPM_ALG_ECDH:
#endif
#if ALG_ECMQV
	  case TPM_ALG_ECMQV:
#endif
#if ALG_RSASSA
	  case TPM_ALG_RSASSA:
#endif
#if ALG_RSAPSS
	  case TPM_ALG_RSAPSS:
#endif
#if ALG_ECDSA
	  case TPM_ALG_ECDSA:
#endif
#if ALG_ECDAA
	  case TPM_ALG_ECDAA:
#endif
#if ALG_SM2
	  case TPM_ALG_SM2:
#endif
#if ALG_ECSCHNORR
	  case TPM_ALG_ECSCHNORR:
#endif
#if ALG_RSAES
	  case TPM_ALG_RSAES:
#endif
#if ALG_OAEP
	  case TPM_ALG_OAEP:
#endif
	    break;
	  case TPM_ALG_NULL:
	    if (allowNull) {
		break;
	    }
	  default:
	    rc = TPM_RC_VALUE;
	}
    }
    return rc;
}