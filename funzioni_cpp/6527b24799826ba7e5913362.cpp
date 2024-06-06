static int proxy_authz(const char **authzid, struct transaction_t *txn)
{
    static char authzbuf[MAX_MAILBOX_BUFFER];
    unsigned authzlen;
    int status;

    syslog(LOG_DEBUG, "STR", *authzid);

    
    if (httpd_userid) {
        free(httpd_userid);
        httpd_userid = NULL;
    }
    if (httpd_extrafolder) {
        free(httpd_extrafolder);
        httpd_extrafolder = NULL;
    }
    if (httpd_extradomain) {
        free(httpd_extradomain);
        httpd_extradomain = NULL;
    }
    if (httpd_authstate) {
        auth_freestate(httpd_authstate);
        httpd_authstate = NULL;
    }

    if (!(config_mupdate_server && config_getstring(IMAPOPT_PROXYSERVERS))) {
        
        syslog(LOG_NOTICE, "STR",
               txn->conn->clienthost, txn->auth_chal.scheme->name, httpd_authid,
               "STR");
        return SASL_NOAUTHZ;
    }

    
    status = mysasl_canon_user(httpd_saslconn, NULL,
                               *authzid, strlen(*authzid),
                               SASL_CU_AUTHZID, NULL,
                               authzbuf, sizeof(authzbuf), &authzlen);
    if (status) {
        syslog(LOG_NOTICE, "STR",
               txn->conn->clienthost, txn->auth_chal.scheme->name,
               beautify_string(*authzid));
        return status;
    }

    
    status = mysasl_proxy_policy(httpd_saslconn, &httpd_proxyctx,
                                 authzbuf, authzlen,
                                 httpd_authid, strlen(httpd_authid),
                                 NULL, 0, NULL);

    if (status) {
        syslog(LOG_NOTICE, "STR",
               txn->conn->clienthost, txn->auth_chal.scheme->name, httpd_authid,
               sasl_errdetail(httpd_saslconn));
        return status;
    }

    *authzid = authzbuf;

    return status;
}