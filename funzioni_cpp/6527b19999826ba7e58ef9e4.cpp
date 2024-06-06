int ssh_scp_push_file64(ssh_scp scp, const char *filename, uint64_t size,
                        int mode)
{
    char buffer[1024] = {0};
    int rc;
    char *file = NULL;
    char *perms = NULL;
    uint8_t code;

    if (scp == NULL) {
        return SSH_ERROR;
    }

    if (scp->state != SSH_SCP_WRITE_INITED) {
        ssh_set_error(scp->session, SSH_FATAL,
                      "STR");
        return SSH_ERROR;
    }

    file = ssh_basename(filename);
    perms = ssh_scp_string_mode(mode);
    SSH_LOG(SSH_LOG_PROTOCOL,
            "STR",
            file, size, perms);
    snprintf(buffer, sizeof(buffer), "STR", perms, size, file);
    SAFE_FREE(file);
    SAFE_FREE(perms);

    rc = ssh_channel_write(scp->channel, buffer, strlen(buffer));
    if (rc == SSH_ERROR) {
        scp->state = SSH_SCP_ERROR;
        return SSH_ERROR;
    }

    rc = ssh_channel_read(scp->channel, &code, 1, 0);
    if (rc <= 0) {
        ssh_set_error(scp->session, SSH_FATAL,
                      "STR",
                      ssh_get_error(scp->session));
        scp->state = SSH_SCP_ERROR;
        return SSH_ERROR;
    }

    if (code != 0) {
        ssh_set_error(scp->session, SSH_FATAL,
                      "STR", code);
        scp->state = SSH_SCP_ERROR;
        return SSH_ERROR;
    }

    scp->filelen = size;
    scp->processed = 0;
    scp->state = SSH_SCP_WRITE_WRITING;

    return SSH_OK;
}