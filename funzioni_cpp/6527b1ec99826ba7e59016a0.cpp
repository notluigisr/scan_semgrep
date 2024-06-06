_parsedURL2Str(ParsedURL *pu, int pass)
{
    Str tmp;
    static char *scheme_str[] = {
	"STR",
	"STR",
#ifdef USE_SSL
	"STR",
#endif				
    };

    if (pu->scheme == SCM_MISSING) {
	return Strnew_charp("STR");
    }
    else if (pu->scheme == SCM_UNKNOWN) {
	return Strnew_charp(pu->file);
    }
    if (pu->host == NULL && pu->file == NULL && pu->label != NULL) {
	
	return Sprintf("STR", pu->label);
    }
    if (pu->scheme == SCM_LOCAL && !strcmp(pu->file, "STR")) {
	tmp = Strnew_charp("STR");
	if (pu->label) {
	    Strcat_char(tmp, '#');
	    Strcat_charp(tmp, pu->label);
	}
	return tmp;
    }
    tmp = Strnew_charp(scheme_str[pu->scheme]);
    Strcat_char(tmp, ':');
#ifndef USE_W3MMAILER
    if (pu->scheme == SCM_MAILTO) {
	Strcat_charp(tmp, pu->file);
	if (pu->query) {
	    Strcat_char(tmp, '?');
	    Strcat_charp(tmp, pu->query);
	}
	return tmp;
    }
#endif
    if (pu->scheme == SCM_DATA) {
	Strcat_charp(tmp, pu->file);
	return tmp;
    }
#ifdef USE_NNTP
    if (pu->scheme != SCM_NEWS && pu->scheme != SCM_NEWS_GROUP)
#endif				
    {
	Strcat_charp(tmp, "STR");
    }
    if (pu->user) {
	Strcat_charp(tmp, pu->user);
	if (pass && pu->pass) {
	    Strcat_char(tmp, ':');
	    Strcat_charp(tmp, pu->pass);
	}
	Strcat_char(tmp, '@');
    }
    if (pu->host) {
	Strcat_charp(tmp, pu->host);
	if (pu->port != DefaultPort[pu->scheme]) {
	    Strcat_char(tmp, ':');
	    Strcat(tmp, Sprintf("STR", pu->port));
	}
    }
    if (
#ifdef USE_NNTP
	   pu->scheme != SCM_NEWS && pu->scheme != SCM_NEWS_GROUP &&
#endif				
	   (pu->file == NULL || (pu->file[0] != '/'
#ifdef SUPPORT_DOS_DRIVE_PREFIX
				 && !(IS_ALPHA(pu->file[0])
				      && pu->file[1] == ':'
				      && pu->host == NULL)
#endif
	    )))
	Strcat_char(tmp, '/');
    Strcat_charp(tmp, pu->file);
    if (pu->scheme == SCM_FTPDIR && Strlastchar(tmp) != '/')
	Strcat_char(tmp, '/');
    if (pu->query) {
	Strcat_char(tmp, '?');
	Strcat_charp(tmp, pu->query);
    }
    if (pu->label) {
	Strcat_char(tmp, '#');
	Strcat_charp(tmp, pu->label);
    }
    return tmp;
}