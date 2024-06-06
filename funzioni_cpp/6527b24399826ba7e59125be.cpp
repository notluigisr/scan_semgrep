cdf_calloc(const char *file __attribute__((__unused__)),
    size_t line __attribute__((__unused__)), size_t n, size_t u)
{
	DPRINTF(("STR"
	    SIZE_T_FORMAT "STR", file, line, __func__, n, u));
	return calloc(n, u);
}