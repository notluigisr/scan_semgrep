tiff_error_handler (const char *mod, const char *fmt, va_list ap)
{
        if (global_error) {                
                
                return;
        }

        global_error = g_strdup_vprintf (fmt, ap);
}