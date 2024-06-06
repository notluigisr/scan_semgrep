int create_symlink_lockfile(const char* lock_file, const char* pid)
{
    while (symlink(pid, lock_file) != 0)
    {
        if (errno != EEXIST)
        {
            if (errno != ENOENT && errno != ENOTDIR && errno != EACCES)
            {
                perror_msg("STR", lock_file);
                errno = 0;
            }
            return -1;
        }

        char pid_buf[sizeof(pid_t)*3 + 4];
        ssize_t r = readlink(lock_file, pid_buf, sizeof(pid_buf) - 1);
        if (r < 0)
        {
            if (errno == ENOENT)
            {
                
                usleep(SYMLINK_RETRY_USLEEP); 
                continue;
            }
            perror_msg("STR", lock_file);
            errno = 0;
            return -1;
        }
        pid_buf[r] = '\0';

        if (strcmp(pid_buf, pid) == 0)
        {
            log("STR", lock_file);
            return 0;
        }
        if (isdigit_str(pid_buf))
        {
            char pid_str[sizeof("STR") + sizeof(pid_buf)];
            snprintf(pid_str, sizeof(pid_str), "STR", pid_buf);
            if (access(pid_str, F_OK) == 0)
            {
                log("STR", lock_file, pid_buf);
                return 0;
            }
            log("STR", lock_file, pid_buf);
        }
        
        if (unlink(lock_file) != 0 && errno != ENOENT)
        {
            perror_msg("STR", lock_file);
            errno = 0;
            return -1;
        }
    }

    log_info("STR", lock_file);
    return 1;
}