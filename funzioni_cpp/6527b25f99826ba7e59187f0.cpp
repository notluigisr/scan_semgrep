get_tc(const char *descriptor,
       int modid,
       int *tc_index,
       struct enum_list **ep, struct range_list **rp, char **hint)
{
    int             i;
    struct tc      *tcp;

    i = get_tc_index(descriptor, modid);
    if (tc_index)
        *tc_index = i;
    if (i != -1) {
        tcp = &tclist[i];
        if (ep) {
            free_enums(ep);
            *ep = copy_enums(tcp->enums);
        }
        if (rp) {
            free_ranges(rp);
            *rp = copy_ranges(tcp->ranges);
        }
        if (hint) {
            if (*hint)
                free(*hint);
            *hint = (tcp->hint ? strdup(tcp->hint) : NULL);
        }
        return tcp->type;
    }
    return LABEL;
}