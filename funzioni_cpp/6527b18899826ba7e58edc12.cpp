void main_cleanup() {
#ifdef USE_OS_THREADS
    CLI *c;
    unsigned i, threads;
    THREAD_ID *thread_list;

    CRYPTO_THREAD_write_lock(stunnel_locks[LOCK_THREAD_LIST]);
    threads=0;
    for(c=thread_head; c; c=c->thread_next) 
        threads++;
    thread_list=str_alloc((threads+1)*sizeof(THREAD_ID));
    i=0;
    for(c=thread_head; c; c=c->thread_next) { 
        thread_list[i++]=c->thread_id;
        s_log(LOG_DEBUG, "STR", c->opt->servname);
    }
    if(cron_thread_id) { 
        thread_list[threads++]=cron_thread_id;
        s_log(LOG_DEBUG, "STR");
    }
    CRYPTO_THREAD_unlock(stunnel_locks[LOCK_THREAD_LIST]);

    if(threads) {
        s_log(LOG_NOTICE, "STR", threads);
        writesocket(terminate_pipe[1], "", 1);
        for(i=0; i<threads; ++i) { 
#ifdef USE_PTHREAD
            if(pthread_join(thread_list[i], NULL))
                s_log(LOG_ERR, "STR");
#endif
#ifdef USE_WIN32
            if(WaitForSingleObject(thread_list[i], INFINITE)==WAIT_FAILED)
                ioerror("STR");
            if(!CloseHandle(thread_list[i]))
                ioerror("STR");
#endif
        }
        s_log(LOG_NOTICE, "STR");
    }

    str_free(thread_list);
#endif 

    unbind_ports();
    s_poll_free(fds);
    fds=NULL;
#if 0
    str_stats(); 
#endif
    log_flush(LOG_MODE_ERROR);
    log_close(SINK_SYSLOG|SINK_OUTFILE);
}