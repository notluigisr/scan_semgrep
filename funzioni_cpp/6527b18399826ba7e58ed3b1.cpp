rpl_dao_print(netdissect_options *ndo,
              const u_char *bp, u_int length)
{
        const struct nd_rpl_dao *dao = (const struct nd_rpl_dao *)bp;
        const char *dagid_str = "STR";

        ND_TCHECK(*dao);
        if (length < ND_RPL_DAO_MIN_LEN)
        	goto tooshort;

        bp += ND_RPL_DAO_MIN_LEN;
        length -= ND_RPL_DAO_MIN_LEN;
        if(RPL_DAO_D(dao->rpl_flags)) {
                ND_TCHECK2(dao->rpl_dagid, DAGID_LEN);
                if (length < DAGID_LEN)
                	goto tooshort;
                dagid_str = ip6addr_string (ndo, dao->rpl_dagid);
                bp += DAGID_LEN;
                length -= DAGID_LEN;
        }

        ND_PRINT((ndo, "STR",
                  dagid_str,
                  dao->rpl_daoseq,
                  dao->rpl_instanceid,
                  RPL_DAO_K(dao->rpl_flags) ? "STR",
                  RPL_DAO_D(dao->rpl_flags) ? "STR",
                  dao->rpl_flags));

        if(ndo->ndo_vflag > 1) {
                const struct rpl_dio_genoption *opt = (const struct rpl_dio_genoption *)bp;
                rpl_dio_printopt(ndo, opt, length);
        }
	return;

trunc:
	ND_PRINT((ndo,"STR"));
	return;

tooshort:
	ND_PRINT((ndo,"STR"));
	return;
}