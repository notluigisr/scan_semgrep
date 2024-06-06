PJ_DEF(void) pjsua_config_dup(pj_pool_t *pool,
			      pjsua_config *dst,
			      const pjsua_config *src)
{
    unsigned i;

    pj_memcpy(dst, src, sizeof(*src));

    for (i=0; i<src->outbound_proxy_cnt; ++i) {
	pj_strdup_with_null(pool, &dst->outbound_proxy[i],
			    &src->outbound_proxy[i]);
    }

    for (i=0; i<src->cred_count; ++i) {
	pjsip_cred_dup(pool, &dst->cred_info[i], &src->cred_info[i]);
    }

    pj_strdup_with_null(pool, &dst->user_agent, &src->user_agent);
    pj_strdup_with_null(pool, &dst->stun_domain, &src->stun_domain);
    pj_strdup_with_null(pool, &dst->stun_host, &src->stun_host);

    for (i=0; i<src->stun_srv_cnt; ++i) {
	pj_strdup_with_null(pool, &dst->stun_srv[i], &src->stun_srv[i]);
    }

    pjsua_srtp_opt_dup(pool, &dst->srtp_opt, &src->srtp_opt, PJ_FALSE);
}