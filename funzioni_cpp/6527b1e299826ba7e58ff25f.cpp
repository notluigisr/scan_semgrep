xmlSchemaPValAttrNodeValue(xmlSchemaParserCtxtPtr pctxt,
			   xmlSchemaBasicItemPtr ownerItem,
			   xmlAttrPtr attr,
			   const xmlChar *value,
			   xmlSchemaTypePtr type)
{

    int ret = 0;

    
    if ((pctxt == NULL) || (type == NULL) || (attr == NULL))
	return (-1);
    if (type->type != XML_SCHEMA_TYPE_BASIC) {
	PERROR_INT("STR",
	    "STR");
	return (-1);
    }
    switch (type->builtInType) {
	case XML_SCHEMAS_NCNAME:
	case XML_SCHEMAS_QNAME:
	case XML_SCHEMAS_ANYURI:
	case XML_SCHEMAS_TOKEN:
	case XML_SCHEMAS_LANGUAGE:
	    ret = xmlSchemaValPredefTypeNode(type, value, NULL,
		(xmlNodePtr) attr);
	    break;
	default: {
	    PERROR_INT("STR",
		"STR"
		"STR");
	    return (-1);
	}
    }
    
    if (ret < 0) {
	PERROR_INT("STR",
	    "STR");
	return (-1);
    } else if (ret > 0) {
	if (WXS_IS_LIST(type))
	    ret = XML_SCHEMAV_CVC_DATATYPE_VALID_1_2_2;
	else
	    ret = XML_SCHEMAV_CVC_DATATYPE_VALID_1_2_1;
	xmlSchemaPSimpleTypeErr(pctxt,
	    ret, ownerItem, (xmlNodePtr) attr,
	    type, NULL, value, NULL, NULL, NULL);
    }
    return (ret);
}