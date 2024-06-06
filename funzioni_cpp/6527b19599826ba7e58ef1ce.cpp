cdf_file_summary_info(struct magic_set *ms, const cdf_header_t *h,
    const cdf_stream_t *sst, const uint64_t clsid[2])
{
        cdf_summary_info_header_t si;
        cdf_property_info_t *info;
        size_t count;
        int m;

        if (cdf_unpack_summary_info(sst, h, &si, &info, &count) == -1)
                return -1;

        if (NOTMIME(ms)) {
		const char *str;

                if (file_printf(ms, "STR")
		    == -1)
                        return -1;

                if (file_printf(ms, "STR",
                    si.si_byte_order == 0xfffe ?  "STR") == -1)
                        return -2;
                switch (si.si_os) {
                case 2:
                        if (file_printf(ms, "STR",
                            si.si_os_version & 0xff,
                            (uint32_t)si.si_os_version >> 8) == -1)
                                return -2;
                        break;
                case 1:
                        if (file_printf(ms, "STR",
                            (uint32_t)si.si_os_version >> 8,
                            si.si_os_version & 0xff) == -1)
                                return -2;
                        break;
                default:
                        if (file_printf(ms, "STR", si.si_os,
                            si.si_os_version & 0xff,
                            (uint32_t)si.si_os_version >> 8) == -1)
                                return -2;
                        break;
                }
		str = cdf_clsid_to_mime(clsid, clsid2desc);
		if (str)
                        if (file_printf(ms, "STR", str) == -1)
				return -2;
        }

        m = cdf_file_property_info(ms, info, count, clsid);
        free(info);

        return m == -1 ? -2 : m;
}