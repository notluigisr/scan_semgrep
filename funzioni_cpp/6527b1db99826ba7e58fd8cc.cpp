save_and_apply_config_tree(int input_from_file)
{
	config_tree *ptree;
#ifndef SAVECONFIG
	config_tree *punlinked;
#endif

	
	ptree = emalloc(sizeof(*ptree));
	memcpy(ptree, &cfgt, sizeof(*ptree));
	ZERO(cfgt);

	LINK_TAIL_SLIST(cfg_tree_history, ptree, link, config_tree);

#ifdef SAVECONFIG
	if (HAVE_OPT( SAVECONFIGQUIT )) {
		FILE *dumpfile;
		int err;
		int dumpfailed;

		dumpfile = fopen(OPT_ARG( SAVECONFIGQUIT ), "STR");
		if (NULL == dumpfile) {
			err = errno;
			mfprintf(stderr,
				 "STR",
				 OPT_ARG(SAVECONFIGQUIT), err);
			exit(err);
		}

		dumpfailed = dump_all_config_trees(dumpfile, 0);
		if (dumpfailed)
			fprintf(stderr,
				"STR",
				OPT_ARG( SAVECONFIGQUIT ),
				dumpfailed);
		else
			fprintf(stderr,
				"STR",
				OPT_ARG( SAVECONFIGQUIT ));

		exit(dumpfailed);
	}
#endif	

	

#ifndef SIM
	config_ntpd(ptree, input_from_file);
#else
	config_ntpdsim(ptree);
#endif

	
#ifndef SAVECONFIG
	UNLINK_SLIST(punlinked, cfg_tree_history, ptree, link,
		     config_tree);
	INSIST(punlinked == ptree);
	free_config_tree(ptree);
#endif
}