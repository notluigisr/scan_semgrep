validate_xargs(krb5_context context,
               krb5_ldap_server_handle *ldap_server_handle,
               const xargs_t *xargs, const char *standalone_dn,
               char *const *subtrees, unsigned int ntrees)
{
    krb5_error_code st;

    if (xargs->dn != NULL) {
        
        st = check_dn_in_container(context, xargs->dn, subtrees, ntrees);
        if (st)
            return st;
        
        st = check_dn_exists(context, ldap_server_handle, xargs->dn, TRUE);
        if (st)
            return st;
    }

    if (xargs->linkdn != NULL) {
        
        st = check_dn_in_container(context, xargs->linkdn, subtrees, ntrees);
        if (st)
            return st;
        
        st = check_dn_exists(context, ldap_server_handle, xargs->linkdn,
                             FALSE);
        if (st)
            return st;
    }

    if (xargs->containerdn != NULL && standalone_dn != NULL) {
        
        st = check_dn_in_container(context, standalone_dn, subtrees, ntrees);
        if (st)
            return st;
    }

    return 0;
}