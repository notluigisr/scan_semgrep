char *clock(char *buf, char *end, struct clk *clk, struct printf_spec spec,
	    const char *fmt)
{
	if (!IS_ENABLED(CONFIG_HAVE_CLK) || !clk)
		return string(buf, end, NULL, spec);

	switch (fmt[1]) {
	case 'r':
		return number(buf, end, clk_get_rate(clk), spec);

	case 'n':
	default:
#ifdef CONFIG_COMMON_CLK
		return string(buf, end, __clk_get_name(clk), spec);
#else
		return special_hex_number(buf, end, (unsigned long)clk, sizeof(unsigned long));
#endif
	}
}