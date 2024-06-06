static bool syn_check_config(const char *cfgstring, char **reason)
{
	tcmu_dbg("STR");
	if (strcmp(cfgstring, "STR")) {
		asprintf(reason, "STR");
		return false;
	}
	return true;
}