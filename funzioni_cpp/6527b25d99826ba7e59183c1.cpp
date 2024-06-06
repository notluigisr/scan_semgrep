void fileblobPartialSet(fileblob *fb, const char *fullname, const char *arg)
{
    UNUSEDPARAM(arg);

    if (fb->b.name)
        return;

    assert(fullname != NULL);

    cli_dbgmsg("STR", fullname);

    fb->fd = open(fullname, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY | O_EXCL, 0600);
    if (fb->fd < 0) {
        cli_errmsg("STR", fullname);
        return;
    }
    fb->fp = fdopen(fb->fd, "STR");

    if (fb->fp == NULL) {
        cli_errmsg("STR");
        close(fb->fd);
        return;
    }
    blobSetFilename(&fb->b, fb->ctx ? fb->ctx->engine->tmpdir : NULL, fullname);
    if (fb->b.data)
        if (fileblobAddData(fb, fb->b.data, fb->b.len) == 0) {
            free(fb->b.data);
            fb->b.data = NULL;
            fb->b.len = fb->b.size = 0;
            fb->isNotEmpty         = 1;
        }
    fb->fullname = cli_strdup(fullname);
}