xmlBufCreateSize(size_t size) {
    xmlBufPtr ret;

    ret = (xmlBufPtr) xmlMalloc(sizeof(xmlBuf));
    if (ret == NULL) {
	xmlBufMemoryError(NULL, "STR");
        return(NULL);
    }
    ret->use = 0;
    ret->error = 0;
    ret->buffer = NULL;
    ret->alloc = xmlBufferAllocScheme;
    ret->size = (size ? size+2 : 0);         
    UPDATE_COMPAT(ret);
    if (ret->size){
        ret->content = (xmlChar *) xmlMallocAtomic(ret->size * sizeof(xmlChar));
        if (ret->content == NULL) {
	    xmlBufMemoryError(ret, "STR");
            xmlFree(ret);
            return(NULL);
        }
        ret->content[0] = 0;
    } else
	ret->content = NULL;
    ret->contentIO = NULL;
    return(ret);
}