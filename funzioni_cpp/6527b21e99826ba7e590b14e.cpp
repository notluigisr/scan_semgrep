static int pam_get_pwd(pam_handle_t *pamh, char **pwd, char *text, int oitem, int nitem)
{
  int rv;
  const char *old_pwd;
  struct pam_conv *conv;
  struct pam_message msg;
  struct pam_response *resp;
  
  const struct pam_message *(msgp[1]);
  msgp[0] = &msg;

  
  if ((oitem == PAM_AUTHTOK) || (oitem == PAM_OLDAUTHTOK)) {
    
    rv = pam_get_item(pamh, oitem, &old_pwd);
    if (rv != PAM_SUCCESS)
      return rv;
    if (old_pwd != NULL) {
      *pwd = strdup(old_pwd);
      return PAM_SUCCESS;
    }
  }

  
  if (text != NULL) {
    msg.msg_style = PAM_PROMPT_ECHO_OFF;
    msg.msg = text;
    rv = pam_get_item(pamh, PAM_CONV, &conv);
    if (rv != PAM_SUCCESS)
      return rv;
    if ((conv == NULL) || (conv->conv == NULL))
      return PAM_CRED_INSUFFICIENT;
    rv = conv->conv(1, msgp, &resp, conv->appdata_ptr);
    if (rv != PAM_SUCCESS)
      return rv;
    if ((resp == NULL) || (resp[0].resp == NULL))
      return PAM_CRED_INSUFFICIENT;
    *pwd = strdup(resp[0].resp);
    
    cleanse(resp[0].resp, strlen(resp[0].resp));
    free(&resp[0]);
    
    if ((nitem == PAM_AUTHTOK) || (nitem == PAM_OLDAUTHTOK)) {
      rv = pam_set_item(pamh, nitem, *pwd);
      if (rv != PAM_SUCCESS)
        return rv;
    }
    return PAM_SUCCESS;
  }
  return PAM_CRED_INSUFFICIENT;
}