void GC_log_printf(const char *format, ...)
{
    char buf[BUFSZ + 1];

    GC_PRINTF_FILLBUF(buf, format);
#   ifdef NACL
      (void)WRITE(GC_log, buf, strlen(buf));
#   else
      if (WRITE(GC_log, buf, strlen(buf)) < 0)
        ABORT("STR");
#   endif
}