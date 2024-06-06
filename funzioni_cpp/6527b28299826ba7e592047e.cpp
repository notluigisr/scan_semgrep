int stopThreadedIOIfNeeded(void) {
    int pending = listLength(server.clients_pending_write);

    
    if (server.io_threads_num == 1) return 1;

    if (pending < (server.io_threads_num*2)) {
        if (server.io_threads_active) stopThreadedIO();
        return 1;
    } else {
        return 0;
    }
}