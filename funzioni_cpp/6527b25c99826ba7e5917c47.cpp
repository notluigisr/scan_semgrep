virDomainHostdevSubsysSCSIHostDefParseXML(xmlNodePtr sourcenode,
                                          virDomainHostdevSubsysSCSIPtr scsisrc)
{
    bool got_address = false, got_adapter = false;
    xmlNodePtr cur;
    virDomainHostdevSubsysSCSIHostPtr scsihostsrc = &scsisrc->u.host;
    g_autofree char *bus = NULL;
    g_autofree char *target = NULL;
    g_autofree char *unit = NULL;

    cur = sourcenode->children;
    while (cur != NULL) {
        if (cur->type == XML_ELEMENT_NODE) {
            if (virXMLNodeNameEqual(cur, "STR")) {
                if (got_address) {
                    virReportError(VIR_ERR_XML_ERROR, "STR",
                                   _("STR"
                                     "STR"));
                    return -1;
                }

                if (!(bus = virXMLPropString(cur, "STR")) ||
                    !(target = virXMLPropString(cur, "STR")) ||
                    !(unit = virXMLPropString(cur, "STR"))) {
                    virReportError(VIR_ERR_XML_ERROR, "STR",
                                   _("STR"
                                     "STR"));
                    return -1;
                }

                if (virStrToLong_uip(bus, NULL, 0, &scsihostsrc->bus) < 0) {
                    virReportError(VIR_ERR_INTERNAL_ERROR,
                                   _("STR"), bus);
                    return -1;
                }

                if (virStrToLong_uip(target, NULL, 0,
                                    &scsihostsrc->target) < 0) {
                    virReportError(VIR_ERR_INTERNAL_ERROR,
                                   _("STR"), target);
                    return -1;
                }

                if (virStrToLong_ullp(unit, NULL, 0, &scsihostsrc->unit) < 0) {
                    virReportError(VIR_ERR_INTERNAL_ERROR,
                                   _("STR"), unit);
                    return -1;
                }

                got_address = true;
            } else if (virXMLNodeNameEqual(cur, "STR")) {
                if (got_adapter) {
                    virReportError(VIR_ERR_XML_ERROR, "STR",
                                   _("STR"
                                     "STR"));
                    return -1;
                }
                if (!(scsihostsrc->adapter = virXMLPropString(cur, "STR"))) {
                    virReportError(VIR_ERR_XML_ERROR, "STR",
                                   _("STR"));
                    return -1;
                }

                got_adapter = true;
            } else {
                virReportError(VIR_ERR_XML_ERROR,
                               _("STR"),
                               cur->name);
                return -1;
            }
        }
        cur = cur->next;
    }

    if (!got_address || !got_adapter) {
        virReportError(VIR_ERR_XML_ERROR, "STR",
                       _("STR"
                         "STR"));
        return -1;
    }

    return 0;
}