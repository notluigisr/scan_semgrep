static char *theme_format_compress_colors(THEME_REC *theme, const char *format)
{
	GString *str;
	char *ret;
	char last_fg, last_bg;

	str = g_string_new(NULL);

	last_fg = last_bg = '\0';
	while (*format != '\0') {
		if (*format == '$') {
                        
			theme_format_append_variable(str, &format);
                        last_fg = last_bg = '\0';
		} else if (*format != '%') {
			
			g_string_append_c(str, *format);
			format++;
		} else {
			
			format++;
			if (IS_OLD_FORMAT(*format, last_fg, last_bg)) {
				
			} else if (IS_FGCOLOR_FORMAT(*format) &&
				   format[1] == '%' &&
				   IS_FGCOLOR_FORMAT(format[2]) &&
				   (*format != 'n' || format[2] == 'n')) {
				
			} else {
				
				g_string_append_c(str, '%');
				g_string_append_c(str, *format);

				if (IS_FGCOLOR_FORMAT(*format))
					last_fg = *format;
				else if (*format == 'Z' || *format == 'X')
					last_fg = '\0';
				if (IS_BGCOLOR_FORMAT(*format))
					last_bg = *format;
				else if (*format == 'z' || *format == 'x')
					last_bg = '\0';
			}
			format++;
		}
	}

	ret = str->str;
        g_string_free(str, FALSE);
        return ret;
}