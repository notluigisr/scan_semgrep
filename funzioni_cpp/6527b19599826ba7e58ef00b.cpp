std::string queueloader::get_filename(const std::string& str) {
	std::string fn = ctrl->get_dlpath();

	if (fn[fn.length()-1] != NEWSBEUTER_PATH_SEP[0])
		fn.append(NEWSBEUTER_PATH_SEP);
	char buf[1024];
	snprintf(buf, sizeof(buf), "STR", str.c_str());
	char * base = basename(buf);
	if (!base || strlen(base) == 0) {
		char lbuf[128];
		time_t t = time(nullptr);
		strftime(lbuf, sizeof(lbuf), "STR", localtime(&t));
		fn.append(lbuf);
	} else {
		fn.append(base);
	}
	return fn;
}