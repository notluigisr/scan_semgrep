request_env(agooReq req, VALUE self) {
    if (Qnil == (VALUE)req->env) {
	volatile VALUE	env = rb_hash_new();

	
	
	

	rb_hash_aset(env, request_method_val, req_method(req));
	rb_hash_aset(env, script_name_val, req_script_name(req));
	rb_hash_aset(env, path_info_val, req_path_info(req));
	rb_hash_aset(env, query_string_val, req_query_string(req));
	rb_hash_aset(env, server_name_val, req_server_name(req));
	rb_hash_aset(env, server_port_val, req_server_port(req));
	fill_headers(req, env);
	rb_hash_aset(env, rack_version_val, rack_version_val_val);
	rb_hash_aset(env, rack_url_scheme_val, req_rack_url_scheme(req));
	rb_hash_aset(env, rack_input_val, req_rack_input(req));
	rb_hash_aset(env, rack_errors_val, req_rack_errors(req));
	rb_hash_aset(env, rack_multithread_val, req_rack_multithread(req));
	rb_hash_aset(env, rack_multiprocess_val, Qfalse);
	rb_hash_aset(env, rack_run_once_val, Qfalse);
	rb_hash_aset(env, rack_logger_val, req_rack_logger(req));
	rb_hash_aset(env, rack_upgrade_val, req_rack_upgrade(req));
	rb_hash_aset(env, rack_hijackq_val, Qtrue);

	
	
	
	
	
	
	
	rb_hash_aset(env, rack_hijack_val, self);
	rb_hash_aset(env, rack_hijack_io_val, Qnil);

	if (agoo_server.rack_early_hints) {
	    volatile VALUE	eh = agoo_early_hints_new(req);

	    rb_hash_aset(env, early_hints_val, eh);
	}
	req->env = (void*)env;
    }
    return (VALUE)req->env;
}