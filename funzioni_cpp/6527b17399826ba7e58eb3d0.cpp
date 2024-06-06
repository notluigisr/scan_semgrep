static void krb5_save_ccname_done(struct tevent_req *req)
{
    struct krb5_auth_state *state = tevent_req_data(req, struct krb5_auth_state);
    struct krb5child_req *kr = state->kr;
    struct pam_data *pd = state->pd;
    int ret;
    char *password = NULL;

    if (kr->is_offline) {
        if (dp_opt_get_bool(kr->krb5_ctx->opts,KRB5_STORE_PASSWORD_IF_OFFLINE)) {
            krb5_pam_handler_cache_auth_step(req);
            return;
        }

        DEBUG(4, ("STR"));
        state->pam_status = PAM_AUTHINFO_UNAVAIL;
        state->dp_err = DP_ERR_OFFLINE;
        ret = EOK;
        goto done;
    }

    if (state->be_ctx->domain->cache_credentials == TRUE) {

        
        state->pam_status = PAM_SUCCESS;
        state->dp_err = DP_ERR_OK;

        switch(pd->cmd) {
            case SSS_PAM_AUTHENTICATE:
            case SSS_CMD_RENEW:
            case SSS_PAM_CHAUTHTOK_PRELIM:
                password = talloc_size(state, pd->authtok_size + 1);
                if (password != NULL) {
                    memcpy(password, pd->authtok, pd->authtok_size);
                    password[pd->authtok_size] = '\0';
                }
                break;
            case SSS_PAM_CHAUTHTOK:
                password = talloc_size(state, pd->newauthtok_size + 1);
                if (password != NULL) {
                    memcpy(password, pd->newauthtok, pd->newauthtok_size);
                    password[pd->newauthtok_size] = '\0';
                }
                break;
            default:
                DEBUG(0, ("STR", pd->cmd));
        }

        if (password == NULL) {
            DEBUG(0, ("STR"));
            ret = EOK; 
            goto done;
        }

        talloc_set_destructor((TALLOC_CTX *)password, password_destructor);

        ret = sysdb_cache_password(state, state->be_ctx->sysdb,
                                   state->be_ctx->domain, pd->user,
                                   password);
        if (ret) {
            DEBUG(2, ("STR"
                      "STR", ret, strerror(ret)));
        }
    }

    state->pam_status = PAM_SUCCESS;
    state->dp_err = DP_ERR_OK;
    ret = EOK;

done:
    if (ret == EOK) {
        tevent_req_done(req);
    } else {
        tevent_req_error(req, ret);
    }

}