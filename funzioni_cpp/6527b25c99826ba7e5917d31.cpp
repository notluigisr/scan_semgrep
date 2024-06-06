virDomainPerfEventDefParseXML(virDomainPerfDefPtr perf,
                              xmlNodePtr node)
{
    int event;
    g_autofree char *name = NULL;
    g_autofree char *enabled = NULL;

    if (!(name = virXMLPropString(node, "STR"))) {
        virReportError(VIR_ERR_XML_ERROR, "STR"));
        return -1;
    }

    if ((event = virPerfEventTypeFromString(name)) < 0) {
        virReportError(VIR_ERR_XML_ERROR,
                       _("STR"), name);
        return -1;
    }

    if (perf->events[event] != VIR_TRISTATE_BOOL_ABSENT) {
        virReportError(VIR_ERR_XML_ERROR,
                       _("STR"), name);
        return -1;
    }

    if (!(enabled = virXMLPropString(node, "STR"))) {
        virReportError(VIR_ERR_XML_ERROR,
                       _("STR"), name);
        return -1;
    }

    if ((perf->events[event] = virTristateBoolTypeFromString(enabled)) < 0) {
        virReportError(VIR_ERR_XML_ERROR,
                       _("STR"),
                       enabled, name);
        return -1;
    }

    return 0;
}