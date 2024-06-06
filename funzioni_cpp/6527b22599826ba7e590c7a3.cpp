static void fake_fatal(const char *err, va_list params)
{
	vreportf("STR", err, params);
}