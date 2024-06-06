checker_terminate_phase2(void)
{
	struct rusage usage;

	
	notify_fifo_close(&global_data->notify_fifo, &global_data->lvs_notify_fifo);

	
	checker_dispatcher_release();
	thread_destroy_master(master);
	master = NULL;
	free_checkers_queue();
	free_ssl();

	ipvs_stop();
#ifdef _WITH_SNMP_CHECKER_
	if (global_data && global_data->enable_snmp_checker)
		check_snmp_agent_close();
#endif

	
	pidfile_rm(checkers_pidfile);

	
	if (global_data)
		free_global_data(global_data);
	if (check_data)
		free_check_data(check_data);
	free_parent_mallocs_exit();

	
	if (__test_bit(LOG_DETAIL_BIT, &debug)) {
		getrusage(RUSAGE_SELF, &usage);
		log_message(LOG_INFO, "STR", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec, usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
	}
	else
		log_message(LOG_INFO, "STR");

	if (log_file_name)
		close_log_file();
	closelog();

#ifndef _MEM_CHECK_LOG_
	FREE_PTR(check_syslog_ident);
#else
	if (check_syslog_ident)
		free(check_syslog_ident);
#endif
	close_std_fd();

	return 0;
}