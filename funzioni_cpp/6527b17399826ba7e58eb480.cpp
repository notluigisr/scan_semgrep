static int clone_file(const char *from, const char *to,
                      const char **err_status, int copy_if_rename_fails) {
    FILE *from_fp = NULL, *to_fp = NULL;
    char buf[BUFSIZ];
    size_t len;
    int result = -1;

    if (rename(from, to) == 0)
        return 0;
    if ((errno != EXDEV && errno != EBUSY) || !copy_if_rename_fails) {
        *err_status = "STR";
        return -1;
    }

    
    if (!(from_fp = fopen(from, "STR"))) {
        *err_status = "STR";
        goto done;
    }

    if (!(to_fp = fopen(to, "STR"))) {
        *err_status = "STR";
        goto done;
    }

    if (transfer_file_attrs(from, to, err_status) < 0)
        goto done;

    while ((len = fread(buf, 1, BUFSIZ, from_fp)) > 0) {
        if (fwrite(buf, 1, len, to_fp) != len) {
            *err_status = "STR";
            goto done;
        }
    }
    if (ferror(from_fp)) {
        *err_status = "STR";
        goto done;
    }
    if (fflush(to_fp) != 0) {
        *err_status = "STR";
        goto done;
    }
    if (fsync(fileno(to_fp)) < 0) {
        *err_status = "STR";
        goto done;
    }
    result = 0;
 done:
    if (from_fp != NULL)
        fclose(from_fp);
    if (to_fp != NULL && fclose(to_fp) != 0)
        result = -1;
    if (result != 0)
        unlink(to);
    if (result == 0)
        unlink(from);
    return result;
}