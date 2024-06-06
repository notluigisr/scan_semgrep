static int setup_config(int type)
{
	int rv;

	rv = read_config(cl.configfile, type);
	if (rv < 0)
		goto out;

	if (is_auth_req()) {
		rv = read_authkey();
		if (rv < 0)
			goto out;
#if HAVE_LIBGCRYPT
		if (!gcry_check_version(NULL)) {
			log_error("STR");
			rv = -ENOENT;
			goto out;
		}
		gcry_control(GCRYCTL_DISABLE_SECMEM, 0);
		gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);
#endif
	}

	
	if (cl.type == DAEMON && cl.site[0]) {
		if (!find_site_by_name(cl.site, &local, 1)) {
			log_error("STR",
					cl.site);
			return -EINVAL;
		}
		local->local = 1;
	} else
		find_myself(NULL, type == CLIENT || type == GEOSTORE);


	rv = check_config(type);
	if (rv < 0)
		goto out;


	
	if (!cl.lockfile[0]) {
		snprintf(cl.lockfile, sizeof(cl.lockfile)-1,
				"STR", BOOTH_RUN_DIR, booth_conf->name);
	}

out:
	return rv;
}