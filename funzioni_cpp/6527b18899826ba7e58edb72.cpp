ipv6_sanity_check(const struct ovs_16aligned_ip6_hdr *nh, size_t size)
{
    uint16_t plen;

    if (OVS_UNLIKELY(size < sizeof *nh)) {
        return false;
    }

    plen = ntohs(nh->ip6_plen);
    if (OVS_UNLIKELY(plen + IPV6_HEADER_LEN > size)) {
        return false;
    }
    
    if (OVS_UNLIKELY(size - (plen + IPV6_HEADER_LEN) > UINT8_MAX)) {
        return false;
    }

    return true;
}