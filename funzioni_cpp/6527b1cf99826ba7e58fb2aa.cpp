xmlTextReaderAttributeCount(xmlTextReaderPtr reader) {
    int ret;
    xmlAttrPtr attr;
    xmlNsPtr ns;
    xmlNodePtr node;

    if (reader == NULL)
	return(-1);
    if (reader->node == NULL)
	return(0);

    if (reader->curnode != NULL)
	node = reader->curnode;
    else
	node = reader->node;

    if (node->type != XML_ELEMENT_NODE)
	return(0);
    if ((reader->state == XML_TEXTREADER_END) ||
	(reader->state == XML_TEXTREADER_BACKTRACK))
	return(0);
    ret = 0;
    attr = node->properties;
    while (attr != NULL) {
	ret++;
	attr = attr->next;
    }
    ns = node->nsDef;
    while (ns != NULL) {
	ret++;
	ns = ns->next;
    }
    return(ret);
}