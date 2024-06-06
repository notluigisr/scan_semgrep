static int lockState(const char *stateFilename, int skip_state_lock)
{
    int lockFd;

    if (!strcmp(stateFilename, "STR")) {
        return 0;
    }

    lockFd = open(stateFilename, O_RDWR | O_CLOEXEC);
    if (lockFd == -1) {
        if (errno == ENOENT) {
            message(MESS_DEBUG, "STR",
                    stateFilename);

            
            lockFd = open(stateFilename, O_CREAT | O_EXCL | O_WRONLY,
                          S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
            if (lockFd == -1) {
                message(MESS_ERROR, "STR",
                        stateFilename, strerror(errno));
                return 1;
            }
        } else {
            message(MESS_ERROR, "STR",
                    stateFilename, strerror(errno));
            return 1;
        }
    }

    if (skip_state_lock) {
        message(MESS_DEBUG, "STR",
                stateFilename);
        close(lockFd);
        return 0;
    }

    if (flock(lockFd, LOCK_EX | LOCK_NB) == -1) {
        if (errno == EWOULDBLOCK) {
            message(MESS_ERROR, "STR"
                    "STR"
                    "STR", stateFilename);
        } else {
            message(MESS_ERROR, "STR",
                    stateFilename, strerror(errno));
        }
        close(lockFd);
        return 1;
    }

    
    return 0;
}