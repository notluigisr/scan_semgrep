char *uwsgi_get_binary_path(char *argvzero) {

#if defined(__linux__) || defined(__CYGWIN__)
	char *buf = uwsgi_calloc(PATH_MAX + 1);
	ssize_t len = readlink("STR", buf, PATH_MAX);
	if (len > 0) {
		return buf;
	}
	free(buf);
#elif defined(_WIN32)
	char *buf = uwsgi_calloc(PATH_MAX + 1);
	if (GetModuleFileName(NULL, buf, PATH_MAX) > 0) {
		return buf;
	}
	free(buf);
#elif defined(__NetBSD__)
	char *buf = uwsgi_calloc(PATH_MAX + 1);
	ssize_t len = readlink("STR", buf, PATH_MAX);
	if (len > 0) {
		return buf;
	}

	if (realpath(argvzero, buf)) {
		return buf;
	}
	free(buf);
#elif defined(__APPLE__)
	char *buf = uwsgi_malloc(uwsgi.page_size);
	uint32_t len = uwsgi.page_size;
	if (_NSGetExecutablePath(buf, &len) == 0) {
		
#ifndef OLD_REALPATH
		char *newbuf = realpath(buf, NULL);
		if (newbuf) {
			free(buf);
			return newbuf;
		}
#endif
	}
	free(buf);
#elif defined(__sun__)
	
	char *buf = (char *) getexecname();
	if (buf) {
		
		if (buf[0] == '/') {
			return buf;
		}

		char *newbuf = uwsgi_malloc(PATH_MAX + 1);
		if (realpath(buf, newbuf)) {
			return newbuf;
		}
	}
#elif defined(__FreeBSD__) || defined(__GNU_kFreeBSD__)
	char *buf = uwsgi_malloc(uwsgi.page_size);
	size_t len = uwsgi.page_size;
	int mib[4];
	mib[0] = CTL_KERN;
	mib[1] = KERN_PROC;
	mib[2] = KERN_PROC_PATHNAME;
	mib[3] = -1;
	if (sysctl(mib, 4, buf, &len, NULL, 0) == 0) {
		return buf;
	}
	free(buf);
#endif


	return argvzero;

}