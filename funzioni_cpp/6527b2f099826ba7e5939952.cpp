static apr_status_t fix_hostname_v6_literal(request_rec *r, char *host)
{
    char *dst;
    int double_colon = 0;

    for (dst = host; *dst; dst++) {
        if (apr_isxdigit(*dst)) {
            if (apr_isupper(*dst)) {
                *dst = apr_tolower(*dst);
            }
        }
        else if (*dst == ':') {
            if (*(dst + 1) == ':') {
                if (double_colon)
                    return APR_EINVAL;
                double_colon = 1;
            }
            else if (*(dst + 1) == '.') {
                return APR_EINVAL;
            }
        }
        else if (*dst == '.') {
            
            if (*(dst + 1) == ':' || *(dst + 1) == '.')
                return APR_EINVAL;
        }
        else {
            return APR_EINVAL;
        }
    }
    return APR_SUCCESS;
}