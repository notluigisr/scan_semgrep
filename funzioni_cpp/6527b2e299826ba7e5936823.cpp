TPMI_RH_HIERARCHY_Marshal(TPMI_RH_HIERARCHY *source, BYTE **buffer, INT32 *size)
{
    UINT16 written = 0;
    written += TPM_HANDLE_Marshal(source, buffer, size);
    return written;
}