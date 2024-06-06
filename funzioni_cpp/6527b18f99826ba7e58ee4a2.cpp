u_char *_our_safe_pcap_next(pcap_t *pcap,  struct pcap_pkthdr *pkthdr,
        const char *funcname, const int line, const char *file)
{
    u_char *pktdata = (u_char *)pcap_next(pcap, pkthdr);

    if (pktdata) {
        if (pkthdr->len > MAXPACKET) {
            fprintf(stderr, "STR",
                    file, funcname, line, pkthdr->len, MAXPACKET);
            exit(-1);
        }

        if (pkthdr->len < pkthdr->caplen) {
            fprintf(stderr, "STR",
                    file, funcname, line, pkthdr->len, pkthdr->caplen);
            exit(-1);
        }
    }

    return pktdata;
}