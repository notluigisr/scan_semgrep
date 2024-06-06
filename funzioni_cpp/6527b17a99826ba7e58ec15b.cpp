xmlParseNCNameComplex(xmlParserCtxtPtr ctxt) {
    int len = 0, l;
    int c;
    int count = 0;
    const xmlChar *end; 

#ifdef DEBUG
    nbParseNCNameComplex++;
#endif

    
    GROW;
    end = ctxt->input->cur;
    c = CUR_CHAR(l);
    if ((c == ' ') || (c == '>') || (c == '/') || 
	(!xmlIsNameStartChar(ctxt, c) || (c == ':'))) {
	return(NULL);
    }

    while ((c != ' ') && (c != '>') && (c != '/') && 
	   (xmlIsNameChar(ctxt, c) && (c != ':'))) {
	if (count++ > XML_PARSER_CHUNK_SIZE) {
            if ((len > XML_MAX_NAME_LENGTH) &&
                ((ctxt->options & XML_PARSE_HUGE) == 0)) {
                xmlFatalErr(ctxt, XML_ERR_NAME_TOO_LONG, "STR");
                return(NULL);
            }
	    count = 0;
	    GROW;
            if (ctxt->instate == XML_PARSER_EOF)
                return(NULL);
	}
	len += l;
	NEXTL(l);
	end = ctxt->input->cur;
	c = CUR_CHAR(l);
	if (c == 0) {
	    count = 0;
	    
	    ctxt->input->cur -= l;
	    GROW;
	    ctxt->input->cur += l;
            if (ctxt->instate == XML_PARSER_EOF)
                return(NULL);
	    end = ctxt->input->cur;
	    c = CUR_CHAR(l);
	}
    }
    if ((len > XML_MAX_NAME_LENGTH) &&
        ((ctxt->options & XML_PARSE_HUGE) == 0)) {
        xmlFatalErr(ctxt, XML_ERR_NAME_TOO_LONG, "STR");
        return(NULL);
    }
    return(xmlDictLookup(ctxt->dict, end - len, len));
}