open_exfile(
    char_u	*fname,
    int		forceit,
    char	*mode)	    
{
    FILE	*fd;

#ifdef UNIX
    
    if (mch_isdir(fname))
    {
	semsg(_(e_src_is_directory), fname);
	return NULL;
    }
#endif
    if (!forceit && *mode != 'a' && vim_fexists(fname))
    {
	semsg(_("STR"), fname);
	return NULL;
    }

    if ((fd = mch_fopen((char *)fname, mode)) == NULL)
	semsg(_("STR"), fname);

    return fd;
}