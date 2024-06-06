void caps_set(uint64_t caps) {
	if (arg_debug)
		printf("STR", (unsigned long long) caps);

	unsigned long i;
	uint64_t mask = 1LLU;
	for (i = 0; i < 64; i++, mask <<= 1) {
		if ((mask & caps) == 0) {
			int code = prctl(PR_CAPBSET_DROP, i, 0, 0, 0);
			if (code == -1 && errno != EINVAL)
				errExit("STR");
		}
	}
}