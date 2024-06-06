void gf_filter_check_output_reconfig(GF_Filter *filter)
{
	u32 i, j;
	
	if (!filter->reconfigure_outputs) return;
	filter->reconfigure_outputs = GF_FALSE;
	
	for (i=0; i<filter->num_output_pids; i++) {
		GF_FilterPid *pid = gf_list_get(filter->output_pids, i);
		for (j=0; j<pid->num_destinations; j++) {
			GF_FilterPidInst *pidi = gf_list_get(pid->destinations, j);
			
			if (pidi->reconfig_pid_props) {
				assert(pidi->props);
				if (pidi->props != pidi->reconfig_pid_props) {
					
					assert(pidi->props->reference_count);
					if (safe_int_dec(& pidi->props->reference_count) == 0) {
						
						gf_mx_p(pidi->pid->filter->tasks_mx);
						gf_list_del_item(pidi->pid->properties, pidi->props);
						gf_mx_v(pidi->pid->filter->tasks_mx);
						gf_props_del(pidi->props);
					}
					pidi->props = pidi->reconfig_pid_props;
					safe_int_inc( & pidi->props->reference_count );
				}
				pidi->reconfig_pid_props = NULL;
				gf_fs_post_task(filter->session, gf_filter_pid_reconfigure_task, pidi->filter, pid, "STR", NULL);
			}
		}
	}
}