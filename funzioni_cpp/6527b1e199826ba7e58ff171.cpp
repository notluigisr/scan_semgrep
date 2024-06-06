xmlOutputBufferFlush(xmlOutputBufferPtr out) {
    int nbchars = 0, ret = 0;

    if ((out == NULL) || (out->error)) return(-1);
    
    if ((out->conv != NULL) && (out->encoder != NULL)) {
	
	do {
	    nbchars = xmlCharEncOutput(out, 0);
	    if (nbchars < 0) {
		xmlIOErr(XML_IO_ENCODER, NULL);
		out->error = XML_IO_ENCODER;
		return(-1);
	    }
	} while (nbchars);
    }

    
    if ((out->conv != NULL) && (out->encoder != NULL) &&
	(out->writecallback != NULL)) {
	ret = out->writecallback(out->context,
                                 (const char *)xmlBufContent(out->conv),
                                 xmlBufUse(out->conv));
	if (ret >= 0)
	    xmlBufShrink(out->conv, ret);
    } else if (out->writecallback != NULL) {
	ret = out->writecallback(out->context,
                                 (const char *)xmlBufContent(out->buffer),
                                 xmlBufUse(out->buffer));
	if (ret >= 0)
	    xmlBufShrink(out->buffer, ret);
    }
    if (ret < 0) {
	xmlIOErr(XML_IO_FLUSH, NULL);
	out->error = XML_IO_FLUSH;
	return(ret);
    }
    out->written += ret;

#ifdef DEBUG_INPUT
    xmlGenericError(xmlGenericErrorContext,
	    "STR", ret);
#endif
    return(ret);
}