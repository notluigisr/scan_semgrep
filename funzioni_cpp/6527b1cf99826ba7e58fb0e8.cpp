static bool ide_bmdma_current_needed(void *opaque)
{
    BMDMAState *bm = opaque;

    return (bm->cur_prd_len != 0);
}