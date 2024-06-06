static uint8_t excluded_channels(bitfile *ld, drc_info *drc)
{
    uint8_t i, n = 0;
    uint8_t num_excl_chan = 7;

    for (i = 0; i < 7; i++)
    {
        drc->exclude_mask[i] = faad_get1bit(ld
            DEBUGVAR(1,103,"STR"));
    }
    n++;

    while ((drc->additional_excluded_chns[n-1] = faad_get1bit(ld
        DEBUGVAR(1,104,"STR"))) == 1)
    {
        for (i = num_excl_chan; i < num_excl_chan+7; i++)
        {
            drc->exclude_mask[i] = faad_get1bit(ld
                DEBUGVAR(1,105,"STR"));
        }
        n++;
        num_excl_chan += 7;
    }

    return n;
}