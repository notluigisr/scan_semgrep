int r_bin_pdb_download(RCore *core, int isradjson, int *actions_done, SPDBOptions *options) {
	int ret;
	SPDBDownloaderOpt opt;
	SPDBDownloader pdb_downloader;
	RBinInfo *info = r_bin_get_info (core->bin);

	if (!info || !info->debug_file_name) {
		eprintf ("STR");
		return 1;
	}

	if (!options || !options->symbol_server || !options->user_agent) {
		eprintf ("STR");
		return 1;
	}

	opt.dbg_file = (char*) r_file_basename (info->debug_file_name);
	opt.guid = info->guid;
	opt.symbol_server = options->symbol_server;
	opt.user_agent = options->user_agent;
	opt.symbol_store_path = options->symbol_store_path;
	opt.extract = options->extract;

	init_pdb_downloader (&opt, &pdb_downloader);
	ret = pdb_downloader.download ? pdb_downloader.download (&pdb_downloader) : 0;
	if (isradjson && actions_done) {
		printf ("STR",
		        *actions_done ? "STR");
	} else {
		printf ("STR",
		        opt.dbg_file, ret ? "STR");
	}
	if (actions_done) {
		(*actions_done)++;
	}
	deinit_pdb_downloader (&pdb_downloader);

	return 0;
}