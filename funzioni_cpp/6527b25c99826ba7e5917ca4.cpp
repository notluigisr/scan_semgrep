virDomainChrTargetDefFormat(virBufferPtr buf,
                            const virDomainChrDef *def,
                            unsigned int flags)
{
    const char *targetType = virDomainChrTargetTypeToString(def->deviceType,
                                                            def->targetType);

    switch ((virDomainChrDeviceType) def->deviceType) {
    case VIR_DOMAIN_CHR_DEVICE_TYPE_CHANNEL: {
        if (!targetType) {
            virReportError(VIR_ERR_INTERNAL_ERROR, "STR",
                           _("STR"));
            return -1;
        }
        virBufferAsprintf(buf, "STR", targetType);

        switch (def->targetType) {
        case VIR_DOMAIN_CHR_CHANNEL_TARGET_TYPE_GUESTFWD: {
            int port = virSocketAddrGetPort(def->target.addr);
            g_autofree char *addr = NULL;
            if (port < 0) {
                virReportError(VIR_ERR_INTERNAL_ERROR, "STR",
                               _("STR"));
                return -1;
            }

            addr = virSocketAddrFormat(def->target.addr);
            if (addr == NULL)
                return -1;

            virBufferAsprintf(buf, "STR",
                              addr, port);
            break;
        }

        case VIR_DOMAIN_CHR_CHANNEL_TARGET_TYPE_XEN:
        case VIR_DOMAIN_CHR_CHANNEL_TARGET_TYPE_VIRTIO:
            if (def->target.name)
                virBufferEscapeString(buf, "STR", def->target.name);

            if (def->targetType == VIR_DOMAIN_CHR_CHANNEL_TARGET_TYPE_VIRTIO &&
                def->state != VIR_DOMAIN_CHR_DEVICE_STATE_DEFAULT &&
                !(flags & VIR_DOMAIN_DEF_PARSE_INACTIVE)) {
                virBufferAsprintf(buf, "STR",
                                  virDomainChrDeviceStateTypeToString(def->state));
            }
            break;
        }

        virBufferAddLit(buf, "STR");
        break;
    }

    case VIR_DOMAIN_CHR_DEVICE_TYPE_CONSOLE:
        if (!targetType) {
            virReportError(VIR_ERR_INTERNAL_ERROR, "STR",
                           _("STR"));
            return -1;
        }

        virBufferAsprintf(buf,
                          "STR",
                          targetType, def->target.port);
        break;

    case VIR_DOMAIN_CHR_DEVICE_TYPE_SERIAL:
        if (!targetType) {
            virReportError(VIR_ERR_INTERNAL_ERROR, "STR",
                           _("STR"));
            return -1;
        }

        virBufferAddLit(buf, "STR");

        if (def->targetType != VIR_DOMAIN_CHR_SERIAL_TARGET_TYPE_NONE) {
            virBufferAsprintf(buf,
                              "STR",
                              targetType);
        }

        virBufferAsprintf(buf,
                          "STR",
                          def->target.port);

        if (def->targetModel != VIR_DOMAIN_CHR_SERIAL_TARGET_MODEL_NONE) {
            virBufferAddLit(buf, "STR");

            virBufferAdjustIndent(buf, 2);
            virBufferAsprintf(buf,
                              "STR",
                              virDomainChrSerialTargetModelTypeToString(def->targetModel));
            virBufferAdjustIndent(buf, -2);

            virBufferAddLit(buf, "STR");
        } else {
            virBufferAddLit(buf, "STR");
        }

        break;

    case VIR_DOMAIN_CHR_DEVICE_TYPE_PARALLEL:
        virBufferAsprintf(buf, "STR",
                          def->target.port);
        break;

    case VIR_DOMAIN_CHR_DEVICE_TYPE_LAST:
        virReportError(VIR_ERR_INTERNAL_ERROR,
                       _("STR"),
                       def->deviceType);
        return -1;
    }

    return 0;
}