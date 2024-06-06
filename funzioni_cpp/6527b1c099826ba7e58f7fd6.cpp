static void openpic_msi_write(void *opaque, hwaddr addr, uint64_t val,
                              unsigned size)
{
    OpenPICState *opp = opaque;
    int idx = opp->irq_msi;
    int srs, ibs;

    DPRINTF("STR",
            __func__, addr, val);
    if (addr & 0xF) {
        return;
    }

    switch (addr) {
    case MSIIR_OFFSET:
        srs = val >> MSIIR_SRS_SHIFT;
        idx += srs;
        ibs = (val & MSIIR_IBS_MASK) >> MSIIR_IBS_SHIFT;
        opp->msi[srs].msir |= 1 << ibs;
        openpic_set_irq(opp, idx, 1);
        break;
    default:
        
        break;
    }
}