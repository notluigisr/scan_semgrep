_rl_read_file (filename, sizep)
     char *filename;
     size_t *sizep;
{
  struct stat finfo;
  size_t file_size;
  char *buffer;
  int i, file;

  if ((stat (filename, &finfo) < 0) || (file = open (filename, O_RDONLY, 0666)) < 0)
    return ((char *)NULL);

  file_size = (size_t)finfo.st_size;

  
  if (file_size != finfo.st_size || file_size + 1 < file_size)
    {
      if (file >= 0)
	close (file);
#if defined (EFBIG)
      errno = EFBIG;
#endif
      return ((char *)NULL);
    }

  
  buffer = (char *)xmalloc (file_size + 1);
  i = read (file, buffer, file_size);
  close (file);

  if (i < 0)
    {
      xfree (buffer);
      return ((char *)NULL);
    }

  RL_CHECK_SIGNALS ();

  buffer[i] = '\0';
  if (sizep)
    *sizep = i;

  return (buffer);
}