void * LibRaw_file_datastream::make_jas_stream()
{
#ifdef NO_JASPER
    return NULL;
#else
#if defined(WIN32) && !defined(__MINGW32__)
	if(wfname())
	{
		jas_file = _wfopen(wfname(),L"STR");
		return jas_stream_fdopen(fileno(jas_file),"STR");
	}
	else
#endif
	{
		return jas_stream_fopen(fname(),"STR");
	}
#endif
}